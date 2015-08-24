/*
 *  Copyright (C) 2013, Samsung Electronics Co. Ltd. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 */

#include    "sec_filter.h"
#include    "tcp_track.h"
#include    "url_parser.h"

#define SKIPSPACE(x)//    {while(*(x) ==' '){(x)=(x)+1;}}

#define METHOD_MAX  3
char    *http_method[METHOD_MAX] = {"GET ", "POST ", "CONNECT "};

int makeNotifyInfo(tcp_TrackInfo *node)
{
    URL_Info    url_info;
    char        *newURL = NULL;
    int         hostLen = 0;
    int         urlLen  = 0;
    int         result  = 0;
    int         referLen    = 0;
    if (node != NULL)
    {
        if (node->host != NULL)
        {
            hostLen = strlen(node->host);
        }
        if (node->url != NULL)
        {
            urlLen  = strlen(node->url);
        }
        if (node->referer != NULL)
        {
            referLen    = strlen(node->referer);
        }
        url_info.id         = node->id;
        url_info.uid        = node->uid;
        url_info.version    = FILTER_VERSION;
        url_info.len        = hostLen+urlLen;       // HOST + URL   not include '\0'
        if (referLen == 0)
        {
        url_info.type       = URL_TYPE;
        node->urlLen        = sizeof(url_info)+url_info.len;
        }
        else
        {
            url_info.type   = URL_REFER_TYPE;
            node->urlLen    = sizeof(url_info)+url_info.len + sizeof(int)+ referLen ;
        }

        newURL  = SEC_MALLOC(node->urlLen+1);
        if (newURL != NULL)
        {
            char    *buffer = newURL;

            memcpy(buffer, &url_info, sizeof(url_info));
            buffer = &buffer[sizeof(url_info)];
            if (hostLen >0)
            {
                memcpy((void *)buffer, (void *)node->host, hostLen);
                SEC_FREE(node->host);
                buffer = &buffer[hostLen];
            }
            if (urlLen >0)
            {
                memcpy((void *)buffer, (void *)node->url, urlLen);
                SEC_FREE(node->url);
                buffer = &buffer[urlLen];
            }
            if (referLen >0)
            {
                *((int *)buffer) = referLen;
                buffer = &buffer[sizeof(int)];
                memcpy((void *)buffer, (void *)node->referer, referLen);
                SEC_FREE(node->referer);
            }
            result              = 1;
            node->notify_Index  = 0;
            node->url           = newURL;
        }
    }
    return result;
}

char *  appendString(char *preData, char *postData)
{
    int     preDataSize     = 0;
    int     postDataSize    = 0;
    int     totalStringSize = 0;
    char    *result         = NULL;

    if ( (preData != NULL) && (postData !=NULL))
    {
        preDataSize     = strlen(preData);
        postDataSize    = strlen(postData);
        if (postDataSize > 0)
        {
            totalStringSize = preDataSize+postDataSize+1;   // Include '\0'
            result  = SEC_MALLOC(totalStringSize);
            if (result != NULL)
            {
                memcpy(result, preData, preDataSize);
                memcpy(&result[preDataSize], postData, postDataSize);
            }
        }
    }
    return result;
}

tcp_TrackInfo*  isURL( struct sk_buff *skb)
{
    char            *request    = NULL;
    int             i           = 0;
    tcp_TrackInfo   *result     = NULL;
    struct	tcphdr  *tcph       = (struct tcphdr *)skb_transport_header(skb);

    if (skb->data_len == 0)
    {
        request = (( char *)tcph + tcph->doff*4);
    }
    else
    {
        struct skb_shared_info *shinfo = skb_shinfo(skb);
        if (shinfo != NULL)
        {
            void *frag_addr = page_address(shinfo->frags[0].page.p) + shinfo->frags[0].page_offset;
            if (frag_addr != NULL)
            {
                request = (char *)frag_addr;
            }
        }
    }
    if (request != NULL)
    {
        for (i = 0; i<METHOD_MAX; i++)
        {
            int	methodLen   = strlen(http_method[i]);
            if (strnicmp(request, http_method[i], methodLen) == 0)
            {
                result = make_tcp_TrackInfo(skb);
                break;
            }
        }
    }
    return result;
}

char * getPacketData( struct sk_buff *skb, tcp_TrackInfo *node)
{
    struct  iphdr   *iph    = (struct iphdr*) ip_hdr(skb);
    struct  tcphdr  *tcph   = (struct tcphdr *)skb_transport_header(skb);
    char            *result = NULL;
    int             length  = skb->len - (iph->ihl*4) - (tcph->doff*4);

    result  = SEC_MALLOC(length+node->buffered+1);
    if (result != NULL)
    {
        if (node->buffered > 0) // If buffered data is exist
        {
            memcpy((void *)result, (void *)node->buffer, node->buffered);   // Copy pre-buffer to current buffer
        }
        if (length >0)
        {
            if (skb->data_len == 0)
            {
                memcpy((void *)&result[node->buffered], (void *)((unsigned char *)tcph + tcph->doff*4) , length);
            }
            else
            {
                int                     i       = 0;
                int                     index   = node->buffered;
                struct skb_shared_info  *shinfo = skb_shinfo(skb);
                for ( i = 0 ; i < shinfo->nr_frags ; i++)
                {
                    void *frag_addr = page_address(shinfo->frags[i].page.p) + shinfo->frags[i].page_offset;
                    if (frag_addr != NULL)
                    {
                        memcpy((void *)&result[index], (void *)frag_addr, shinfo->frags[i].size);
                        index += shinfo->frags[i].size;
                    }
                }
            }
        }
        result[length+node->buffered] = 0;
        node->buffered = 0;
    }
    return result;
}


int saveToBuffer(tcp_TrackInfo *node, char *data, int size)
{
    int bufferSize  = 0;
    int result      = 0;
    if (size < PREPACKET_BUFFER_SIZE)
    {
        bufferSize  = size;
    }
    else
    {
        bufferSize  = PREPACKET_BUFFER_SIZE;
    }
    result  = size-bufferSize;
    memcpy((void *)node->buffer, (void *)&data[result] , bufferSize);
    data[result] = 0;
    node->buffered = bufferSize;
    return result;
}

int findStringByTag(tcp_TrackInfo *node, char **data, char *dataStart,  char *tagInfo)
{
    char    *dataEnd    = NULL;
    int     len         = 0;
    int     result      = -1;

    if ((dataStart != NULL) && (tagInfo != NULL))
    {
        dataEnd     = strstr(dataStart, tagInfo);
        if (dataEnd != NULL)    // Found End String
        {
            *dataEnd    = 0;
            len         = strlen(dataStart);
            result      = len;      // result has length only when tag's been found
        }
        else    // Next Packet is needed
        {
            int dataLen = strlen(dataStart);
            len = saveToBuffer(node, dataStart, dataLen);   // Last buffer size after back-up
        }

        if (*data != NULL)  //Place to Save has previous string
        {
            char *newData   = appendString(*data, dataStart);
            if (newData != NULL)    //Get appended string
            {
                SEC_FREE(*data);
                *data = newData;    // Replace with New URL
            }
        }
        else if (len >0)    // This is FIrst block of data
        {
            char *newData   = NULL;
            newData = SEC_MALLOC(len+1);
            if (newData != NULL)
            {
                memcpy((void *)newData, (void *)dataStart, len);
                newData[len] =0;
                *data = newData;
            }
        }
    }
    return result;
}


void    getURL(char *request, tcp_TrackInfo *node)  // request is already checked
{
    int     len         = 0;
    int     length      = 0;
    int     i           = 0;
    int     flagLast    = 0;
    char    *dataStart  = request;

    length          = strlen(dataStart);
    if ((length >= 4) && (strcmp(&dataStart[length-4], "\r\n\r\n") == 0))
    {
        flagLast = 1;
    }

    if (node->status == NOTSET)     // This is first Packet
    {
        for (i = 0 ; i<METHOD_MAX ; i++)
        {
            int	methodLen   = strlen(http_method[i]);
            if (strnicmp(request, http_method[i], methodLen) == 0)  // Request Line should be started with Method Name
            {
                node->status    = GETTING_URL;
                dataStart       = &request[methodLen];
                SKIPSPACE(dataStart);
                len             = findStringByTag(node, &(node->url), dataStart, " HTTP/");
                if (len >= 0)
                {
                    node->status = GOT_URL;
                    dataStart= &dataStart[len+1];
                }
                break;
            }
        }
    }
    else if (node->status == GETTING_URL)
    {
        len = findStringByTag(node, &(node->url), dataStart, " HTTP/");
        if (len >= 0)
        {
            node->status = GOT_URL;
            dataStart= &dataStart[len+1];
        }
    }

    if (node->status == GOT_URL)
    {
        char    *referer        = NULL;
        char    *hostStart      = NULL;
        if ((filterMode == FILTER_MODE_ON_BLOCK_REFER) ||(filterMode == FILTER_MODE_ON_RESPONSE_REFER))
        {
            if (node->referer == NULL)
            {
                referer = strstr(dataStart, "\r\nReferer: ");
                if (referer != NULL)
                {
                    referer = &referer[11];
                }
            }
        }
        if ((node->host == NULL) && (node->url[0] == '/'))        // Need to find HOST
        {
            hostStart = strstr(dataStart, "\r\nHost: ");  // Find Host:
            if (hostStart !=NULL)
            {
                hostStart   = &hostStart[8];
            }
        }

        if ((referer != NULL) && (hostStart != NULL))
        {
            if (referer<hostStart)  // referer is first and it should finished before host starting
            {
                SKIPSPACE(referer);
                findStringByTag(node, &(node->referer), referer, "\r\n");
                SKIPSPACE(hostStart);
                if (findStringByTag(node, &(node->host), hostStart, "\r\n") >=0)
                {
                    node->status = GOT_FULL_URL;  //
                }
                else
                {
                node->status    = GETTING_HOST;
                }
            }
            else        // Host is first and referer is next
            {
                SKIPSPACE(hostStart);
                findStringByTag(node, &(node->host), hostStart, "\r\n");
                SKIPSPACE(referer);
                if (findStringByTag(node, &(node->referer), referer, "\r\n")>=0)
                {
                    node->status = GOT_FULL_URL;
                }
                else
                {
                    node->status = GETTING_REFERER;
                }
            }
        }else if (referer != NULL)
        {
            SKIPSPACE(referer);
            if (findStringByTag(node, &(node->referer), referer, "\r\n") >=0)
            {
                if (flagLast == 1)
                {
                    node->status = GOT_FULL_URL;
            }
            else
            {
                    node->status = GOT_URL;
                }
            }
            else
            {
                node->status = GETTING_REFERER;
            }
        }
        else if (hostStart != NULL)
        {
            SKIPSPACE(hostStart);
            if (findStringByTag(node, &(node->host), hostStart, "\r\n")>=0)
            {
                if (flagLast == 1)
                {
                    node->status = GOT_FULL_URL;
                }
                else
                {
                    node->status = GOT_URL;
                }
            }
            else
            {
                node->status = GETTING_REFERER;
            }
        }
        else
        {
            if (flagLast == 1)  // This is last packet
            {
            node->status    = GOT_FULL_URL;
        }
            else
            {
                saveToBuffer(node, dataStart, length);
            }
        }
    }
    else if (node->status == GETTING_HOST)
    {
        if (findStringByTag(node, &(node->host), dataStart, "\r\n")>=0)
        {
            if (flagLast == 1)
            {
            node->status = GOT_FULL_URL;
        }
            else
            {
                node->status = GOT_URL;
            }
        }
    }
    else if (node->status == GETTING_REFERER)
    {
        if (findStringByTag(node, &(node->referer), dataStart, "\r\n")>=0)
        {
            if (flagLast == 1)
            {
                node->status = GOT_FULL_URL;
            }
            else
            {
                node->status = GOT_URL;
            }
        }
    }
}
