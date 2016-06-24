/*
** =========================================================================
** File:
**     VibeOSKernelLinuxTime.c
**
** Description:
**     High Resolution Time helper functions for Linux.
**
** Portions Copyright (c) 2008-2010 Immersion Corporation. All Rights Reserved.
**
** This file contains Original Code and/or Modifications of Original Code
** as defined in and that are subject to the Immersion Open Source License ?
** January 2008 (the 'License'). You may not use this file except in
** compliance with the License. Please obtain a copy of the License by
** opening the file named "Immersion Open Source License ?January 2008.txt"
** that resides in the same folder as the source file tspdrv.c in your
** development package. Alternately, a copy of the Immersion Open Source
** License ?January 2008 can be obtained from Immersion Corporation by
** requesting one via an email addressed to TouchSenseSales@immersion.com.
**
** The Original Code and all software distributed under the License are
** distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
** EXPRESS OR IMPLIED, AND IMMERSION HEREBY DISCLAIMS ALL SUCH WARRANTIES,
** INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS
** FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. Please see
** the License for the specific language governing rights and limitations
** under the License.
** ========================================================================
 */

/*
 ** Kernel high-resolution software timer is used as an example but another type
 ** of timer (such as HW timer or standard software timer) might be used to achieve
 ** the 5ms required rate.
 */

#ifndef CONFIG_HIGH_RES_TIMERS
#warning "The Kernel does not have high resolution timers enabled. Either provide a non hr-timer implementation of VibeOSKernelLinuxTime.c or re-compile your kernel with CONFIG_HIGH_RES_TIMERS=y"
#endif

#include <linux/hrtimer.h>
#include <linux/mutex.h>
#include <linux/kthread.h>

#define WATCHDOG_TIMEOUT                10      /* 10 timer cycles = 50ms */

/* Global variables */
static bool g_bTimerThreadStarted = false;
static bool g_bTimerStarted = false;
static struct hrtimer g_tspTimer;
static ktime_t g_ktFiveMs;
struct task_struct  *g_pTspThread;
static int g_nWatchdogCounter = 0;

DECLARE_COMPLETION(g_tspCompletion);
//DECLARE_MUTEX(g_hMutex);
struct semaphore g_hMutex = __SEMAPHORE_INITIALIZER(g_hMutex, 1);

/* Forward declarations */
static void VibeOSKernelLinuxStartTimer(void);
static void VibeOSKernelLinuxStopTimer(void);

/**
 * VibeSemIsLocked - is the semaphore locked
 * @lock: the semaphore to be queried
 *
 * Returns 1 if the semaphore is locked, 0 if unlocked.
 */
static inline int VibeSemIsLocked(struct semaphore *lock)
{
#if ((LINUX_VERSION_CODE & 0xFFFFFF) < KERNEL_VERSION(2,6,27))
    return atomic_read(&lock->count) != 1;
#else
    return (lock->count) != 1;
#endif
}


static enum hrtimer_restart tsp_timer_interrupt(struct hrtimer *timer)
{
    /* Scheduling next timeout value right away */
    hrtimer_forward_now(timer, g_ktFiveMs);

    if(g_bTimerStarted)
    {
        /* Notifying the handler of this timer of the tick  */
        /* This allows us to perform operations that are usually */
        /* not allowed inside interrupt context, such as locking */
        /* a mutex, etc. */
        complete(&g_tspCompletion);
    }

    return HRTIMER_RESTART;
}


static int VibeOSKernelTimerProc(void* data)
{
    int nActuatorNotPlaying;
    int i;
    int bReachEndBuffer = 0;
    while(!kthread_should_stop())
    {
        if(g_bTimerThreadStarted)
        {
            /* Block until we get woken up by timer tick */
            /* . only do this if we're not exiting entirely */
            wait_for_completion_interruptible(&g_tspCompletion);

            /* Reinitialized completion so it isn't free by default */
            init_completion(&g_tspCompletion);
        }

        nActuatorNotPlaying = 0;

        /* Return right away if timer is not supposed to run */
        if (g_bTimerStarted)
	{
            for (i = 0; i < NUM_ACTUATORS; i++)
	    {
                actuator_samples_buffer *pCurrentActuatorSample = &(g_SamplesBuffer[i]);

                if (-1 == pCurrentActuatorSample->nIndexPlayingBuffer)
                {
                    nActuatorNotPlaying++;
                    if ((NUM_ACTUATORS == nActuatorNotPlaying) && ((++g_nWatchdogCounter) > WATCHDOG_TIMEOUT))
                    {
                        /* Nothing to play for all actuators, turn off the timer when we reach the watchdog tick count limit */
                        ImmVibeSPI_ForceOut_Set(i, 0);
                        ImmVibeSPI_ForceOut_AmpDisable(i);
                        VibeOSKernelLinuxStopTimer();
                        /* Reset watchdog counter */
                        g_nWatchdogCounter = 0;
                    }
                }
                else
                {
                    /* Play the current buffer */
                    ImmVibeSPI_ForceOut_Set(i, pCurrentActuatorSample->actuatorSamples[(int)pCurrentActuatorSample->nIndexPlayingBuffer].dataBuffer[(int)(pCurrentActuatorSample->nIndexOutputValue++)]);
		    if (pCurrentActuatorSample->nIndexOutputValue >= pCurrentActuatorSample->actuatorSamples[(int)pCurrentActuatorSample->nIndexPlayingBuffer].nBufferSize)
                    {
                        /* We were playing in the last tick */
			    /* Reach the end of the current buffer */
                        pCurrentActuatorSample->actuatorSamples[(int)pCurrentActuatorSample->nIndexPlayingBuffer].nBufferSize = 0;
			bReachEndBuffer = 1;

                        /* Check stop request and empty buffer */
                        if ((g_bStopRequested) || (0 == (pCurrentActuatorSample->actuatorSamples[(int)((pCurrentActuatorSample->nIndexPlayingBuffer) ^ 1)].nBufferSize)))
                        {
                            pCurrentActuatorSample->nIndexPlayingBuffer = -1;
			    if(g_bStopRequested)
                            {
                                /* g_bStopReqested is set, so turn off all actuators */
                                ImmVibeSPI_ForceOut_Set(i, 0);
                                ImmVibeSPI_ForceOut_AmpDisable(i);
				/* If it's the last actuator, stop the timer */
                                if (i == (NUM_ACTUATORS-1))
                                {
                                    VibeOSKernelLinuxStopTimer();

                                    /* Reset watchdog counter */
                                    g_nWatchdogCounter = 0;
                                }
                            }
                        }
                        else  /* The other buffer has data in it */
                        {
                            /* Switch buffer */
                            (pCurrentActuatorSample->nIndexPlayingBuffer) ^= 1;
                            pCurrentActuatorSample->nIndexOutputValue = 0;
                        }
                    }
                }
            }

            /* Release the mutex if locked */
            if (bReachEndBuffer && VibeSemIsLocked(&g_hMutex))
            {
                up(&g_hMutex);
            }
        }
    }

    return 0;
}

static void VibeOSKernelLinuxInitTimer(void)
{
    /* Get a 5,000,000ns = 5ms time value */
    g_ktFiveMs = ktime_set(0, 5000000);

    /* Start the companion thread. It's controlled by the timer, so when that is stopped, we're OK. */
    g_bTimerThreadStarted = true;
    g_pTspThread = kthread_run(VibeOSKernelTimerProc, NULL, "TouchSense Player Thread");

    hrtimer_init(&g_tspTimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

    /* Initialize a 5ms-timer with tsp_timer_interrupt as timer callback (interrupt driven)*/
    g_tspTimer.function = tsp_timer_interrupt;
}

static void VibeOSKernelLinuxStartTimer(void)
{
    int i;

    /* Reset watchdog counter */
    g_nWatchdogCounter = 0;

    if (!g_bTimerStarted)
    {
        if (!VibeSemIsLocked(&g_hMutex))
        {
			if(down_interruptible(&g_hMutex)) /* start locked */
			{
				//printk("down_interruptible failed");
			}
        }

        g_bTimerStarted = true;

        /* Start the timer */
        hrtimer_start(&g_tspTimer, g_ktFiveMs, HRTIMER_MODE_REL);
	/* Don't block the write() function after the first sample to allow the host sending the next samples with no delay */
        for (i = 0; i < NUM_ACTUATORS; i++)
        {
           if ((g_SamplesBuffer[i].actuatorSamples[0].nBufferSize) || (g_SamplesBuffer[i].actuatorSamples[1].nBufferSize))
           {
               g_SamplesBuffer[i].nIndexOutputValue = 0;
               return;
           }
        }
    }

    /*
     ** Use interruptible version of down to be safe
     ** (try to not being stuck here if the mutex is not freed for any reason)
    */
	if(down_interruptible(&g_hMutex)) /* wait for the mutex to be freed by the timer */
	{
		//printk("down_interruptible failed");
	}
}

static void VibeOSKernelLinuxStopTimer(void)
{
    int i;

    if (g_bTimerStarted)
    {
        g_bTimerStarted = false;
        hrtimer_cancel(&g_tspTimer);
    }

     /* Reset samples buffers */
     for (i = 0; i < NUM_ACTUATORS; i++)
     {
         g_SamplesBuffer[i].nIndexPlayingBuffer = -1;
         g_SamplesBuffer[i].actuatorSamples[0].nBufferSize = 0;
         g_SamplesBuffer[i].actuatorSamples[1].nBufferSize = 0;
     }
     g_bStopRequested = false;
     g_bIsPlaying = false;
}

static void VibeOSKernelLinuxTerminateTimer(void)
{
    VibeOSKernelLinuxStopTimer();
    g_bTimerThreadStarted = false;
    complete_all(&g_tspCompletion);
    kthread_stop(g_pTspThread);
    if (VibeSemIsLocked(&g_hMutex)) up(&g_hMutex);
}
