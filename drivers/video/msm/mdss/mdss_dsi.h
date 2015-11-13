/* Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef MDSS_DSI_H
#define MDSS_DSI_H

#include <linux/list.h>
#include <mach/scm-io.h>

#include "mdss_panel.h"
#include "mdss_io_util.h"
#include "mdss_dsi_cmd.h"

#define MMSS_SERDES_BASE_PHY 0x04f01000 /* mmss (De)Serializer CFG */

#define MIPI_OUTP(addr, data) writel_relaxed((data), (addr))
#define MIPI_INP(addr) readl_relaxed(addr)

#ifdef CONFIG_MSM_SECURE_IO
#define MIPI_OUTP_SECURE(addr, data) secure_writel((data), (addr))
#define MIPI_INP_SECURE(addr) secure_readl(addr)
#else
#define MIPI_OUTP_SECURE(addr, data) writel_relaxed((data), (addr))
#define MIPI_INP_SECURE(addr) readl_relaxed(addr)
#endif

#define MIPI_DSI_PRIM 1
#define MIPI_DSI_SECD 2

#define MIPI_DSI_PANEL_VGA	0
#define MIPI_DSI_PANEL_WVGA	1
#define MIPI_DSI_PANEL_WVGA_PT	2
#define MIPI_DSI_PANEL_FWVGA_PT	3
#define MIPI_DSI_PANEL_WSVGA_PT	4
#define MIPI_DSI_PANEL_QHD_PT 5
#define MIPI_DSI_PANEL_WXGA	6
#define MIPI_DSI_PANEL_WUXGA	7
#define MIPI_DSI_PANEL_720P_PT	8
#define DSI_PANEL_MAX	8

//#define DSI_CLK_DEBUG

enum {		/* mipi dsi panel */
	DSI_VIDEO_MODE,
	DSI_CMD_MODE,
};

enum {
	ST_DSI_CLK_OFF,
	ST_DSI_SUSPEND,
	ST_DSI_RESUME,
	ST_DSI_PLAYING,
	ST_DSI_NUM
};

enum {
	EV_DSI_UPDATE,
	EV_DSI_DONE,
	EV_DSI_TOUT,
	EV_DSI_NUM
};

enum {
	LANDSCAPE = 1,
	PORTRAIT = 2,
};

enum dsi_trigger_type {
	DSI_CMD_MODE_DMA,
	DSI_CMD_MODE_MDP,
};

enum dsi_panel_bl_ctrl {
	BL_PWM,
	BL_WLED,
	BL_DCS_CMD,
	BL_GPIO_SWING,
	UNKNOWN_CTRL,
};

enum dsi_panel_status_mode {
	ESD_BTA,
	ESD_REG,
	ESD_MAX,
};

enum dsi_ctrl_op_mode {
	DSI_LP_MODE,
	DSI_HS_MODE,
};

enum dsi_lane_map_type {
	DSI_LANE_MAP_0123,
	DSI_LANE_MAP_3012,
	DSI_LANE_MAP_2301,
	DSI_LANE_MAP_1230,
	DSI_LANE_MAP_0321,
	DSI_LANE_MAP_1032,
	DSI_LANE_MAP_2103,
	DSI_LANE_MAP_3210,
};

#define CTRL_STATE_UNKNOWN		0x00
#define CTRL_STATE_PANEL_INIT		BIT(0)
#define CTRL_STATE_MDP_ACTIVE		BIT(1)

#define DSI_NON_BURST_SYNCH_PULSE	0
#define DSI_NON_BURST_SYNCH_EVENT	1
#define DSI_BURST_MODE			2

#define DSI_RGB_SWAP_RGB	0
#define DSI_RGB_SWAP_RBG	1
#define DSI_RGB_SWAP_BGR	2
#define DSI_RGB_SWAP_BRG	3
#define DSI_RGB_SWAP_GRB	4
#define DSI_RGB_SWAP_GBR	5

#define DSI_VIDEO_DST_FORMAT_RGB565		0
#define DSI_VIDEO_DST_FORMAT_RGB666		1
#define DSI_VIDEO_DST_FORMAT_RGB666_LOOSE	2
#define DSI_VIDEO_DST_FORMAT_RGB888		3

#define DSI_CMD_DST_FORMAT_RGB111	0
#define DSI_CMD_DST_FORMAT_RGB332	3
#define DSI_CMD_DST_FORMAT_RGB444	4
#define DSI_CMD_DST_FORMAT_RGB565	6
#define DSI_CMD_DST_FORMAT_RGB666	7
#define DSI_CMD_DST_FORMAT_RGB888	8

#define DSI_INTR_ERROR_MASK		BIT(25)
#define DSI_INTR_ERROR			BIT(24)
#define DSI_INTR_BTA_DONE_MASK          BIT(21)
#define DSI_INTR_BTA_DONE               BIT(20)
#define DSI_INTR_VIDEO_DONE_MASK	BIT(17)
#define DSI_INTR_VIDEO_DONE		BIT(16)
#define DSI_INTR_CMD_MDP_DONE_MASK	BIT(9)
#define DSI_INTR_CMD_MDP_DONE		BIT(8)
#define DSI_INTR_CMD_DMA_DONE_MASK	BIT(1)
#define DSI_INTR_CMD_DMA_DONE		BIT(0)

#define DSI_CMD_TRIGGER_NONE		0x0	/* mdp trigger */
#define DSI_CMD_TRIGGER_TE		0x02
#define DSI_CMD_TRIGGER_SW		0x04
#define DSI_CMD_TRIGGER_SW_SEOF		0x05	/* cmd dma only */
#define DSI_CMD_TRIGGER_SW_TE		0x06

#define DSI_VIDEO_TERM  BIT(16)
#define DSI_MDP_TERM    BIT(8)
#define DSI_BTA_TERM    BIT(1)
#define DSI_CMD_TERM    BIT(0)

extern struct device dsi_dev;
extern int mdss_dsi_clk_on;
extern u32 dsi_irq;
extern struct mdss_dsi_ctrl_pdata *ctrl_list[];

struct dsiphy_pll_divider_config {
	u32 clk_rate;
	u32 fb_divider;
	u32 ref_divider_ratio;
	u32 bit_clk_divider;	/* oCLK1 */
	u32 byte_clk_divider;	/* oCLK2 */
	u32 analog_posDiv;
	u32 digital_posDiv;
};

extern struct dsiphy_pll_divider_config pll_divider_config;

struct dsi_clk_mnd_table {
	u8 lanes;
	u8 bpp;
	u8 pll_digital_posDiv;
	u8 pclk_m;
	u8 pclk_n;
	u8 pclk_d;
};

static const struct dsi_clk_mnd_table mnd_table[] = {
	{ 1, 2,  8, 1, 1, 0},
	{ 1, 3, 12, 1, 1, 0},
	{ 2, 2,  4, 1, 1, 0},
	{ 2, 3,  6, 1, 1, 0},
	{ 3, 2,  1, 3, 8, 4},
	{ 3, 3,  4, 1, 1, 0},
	{ 4, 2,  2, 1, 1, 0},
	{ 4, 3,  3, 1, 1, 0},
};

struct dsi_clk_desc {
	u32 src;
	u32 m;
	u32 n;
	u32 d;
	u32 mnd_mode;
	u32 pre_div_func;
};

#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQHD_PT_PANEL)
#define DEBUG_LDI_STATUS
#define DYNAMIC_FPS_USE_TE_CTRL
extern int dynamic_fps_use_te_ctrl;
#endif

struct dsi_cmd {
	struct dsi_cmd_desc *cmd_desc;
	char *read_size;
	char *read_startoffset;
	int num_of_cmds;
	char *cmds_buff;
	int cmds_len;
};
struct dsi_panel_cmds {
	char *buf;
	int blen;
	struct dsi_cmd_desc *cmds;
	int cmd_cnt;
	int link_state;
};

#define CMD_REQ_SINGLE_TX 0x0010

struct dsi_kickoff_action {
	struct list_head act_entry;
	void (*action) (void *);
	void *data;
};

struct dsi_drv_cm_data {
	struct regulator *vdd_vreg;
	struct regulator *vdd_io_vreg;
	struct regulator *vdda_vreg;
	struct regulator *iovdd_vreg;
	int broadcast_enable;
};

enum {
	DSI_CTRL_0,
	DSI_CTRL_1,
	DSI_CTRL_MAX,
};

/* DSI controller #0 is always treated as a master in broadcast mode */
#define DSI_CTRL_MASTER		DSI_CTRL_0
#define DSI_CTRL_SLAVE		DSI_CTRL_1

#define DSI_BUS_CLKS	BIT(0)
#define DSI_LINK_CLKS	BIT(1)
#define DSI_ALL_CLKS	((DSI_BUS_CLKS) | (DSI_LINK_CLKS))

#define DSI_EV_PLL_UNLOCKED		0x0001
#define DSI_EV_MDP_FIFO_UNDERFLOW	0x0002
#define DSI_EV_DSI_FIFO_EMPTY		0x0003
#define DSI_EV_MDP_BUSY_RELEASE		0x80000000

struct mdss_dsi_ctrl_pdata {
	int ndx;	/* panel_num */
	int (*on) (struct mdss_panel_data *pdata);
	int (*off) (struct mdss_panel_data *pdata);
#if defined (CONFIG_FB_MSM_MDSS_S6E8AA0A_HD_PANEL)
	int (*mtp) (struct mdss_panel_data *pdata);
#endif
	int (*partial_update_fnc) (struct mdss_panel_data *pdata);
	int (*check_status) (struct mdss_dsi_ctrl_pdata *pdata);
	int (*cmdlist_commit)(struct mdss_dsi_ctrl_pdata *ctrl, int from_mdp);
	void (*switch_mode) (struct mdss_panel_data *pdata, int mode);
	int (*registered) (struct mdss_panel_data *pdata);
	int (*dimming_init) (struct mdss_panel_data *pdata);
	int (*event_handler) (int e);
	int (*panel_blank) (struct mdss_panel_data *pdata, int blank);
	void (*panel_reset) (struct mdss_panel_data *pdata, int enable);
	int (*panel_extra_power) (struct mdss_panel_data *pdata, int enable);
	void (*bl_fnc) (struct mdss_panel_data *pdata, u32 level);
	struct mdss_panel_data panel_data;
	unsigned char *ctrl_base;
	struct dss_io_data ctrl_io;
	struct dss_io_data mmss_misc_io;
	struct dss_io_data phy_io;
	int reg_size;
	u32 bus_clk_cnt;
	u32 link_clk_cnt;
	u32 flags;
	u32 clk_cnt;
	u32 clk_cnt_by_dsi1;
	struct clk *mdp_core_clk;
	struct clk *ahb_clk;
	struct clk *axi_clk;
	struct clk *mmss_misc_ahb_clk;
	struct clk *byte_clk;
	struct clk *esc_clk;
	struct clk *pixel_clk;
	u8 ctrl_state;
	int panel_mode;
	int irq_cnt;
	int mdss_dsi_clk_on;
	int rst_gpio;
	int disp_en_gpio;
	int disp_en_gpio2;
#if defined(CONFIG_FB_MSM_MDSS_HX8394C_TFT_VIDEO_720P_PANEL)
	int disp_en_vsp_gpio;
	int disp_en_vsn_gpio;
#endif
#if defined(CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_CMD_WQXGA_S6TNMR7_PT_PANEL)
	int tcon_ready_gpio;
#endif
#if defined(CONFIG_FB_MSM_MDSS_MAGNA_OCTA_VIDEO_720P_PANEL)
	int lcd_crack_det;
	int expander_enble_gpio;
#endif
#if defined(CONFIG_FB_MSM_MDSS_SHARP_HD_PANEL)
	int disp_en_gpio_p;
	int disp_en_gpio_n;
#endif
#if defined(CONFIG_FB_MSM_MIPI_MAGNA_OCTA_VIDEO_WXGA_PT_DUAL_PANEL)
	int lcd_crack_det_gpio;
	int lcd_esd_det_gpio;
	int lcd_sel_gpio;
	struct regulator *lcd_3p0_vreg;
	struct regulator *lcd_1p8_vreg;
#endif
	int bl_on_gpio;
	int disp_te_gpio;
	int mode_gpio;
	int rst_gpio_requested;
	int disp_en_gpio_requested;
	int disp_te_gpio_requested;
	int mode_gpio_requested;
	int bklt_ctrl;	/* backlight ctrl */
	int pwm_period;
	int pwm_pmic_gpio;
	int pwm_lpg_chan;
	int bklt_max;
	int new_fps;
	int pwm_enabled;
#if defined(CONFIG_CABC_TUNING_HX8394C)
	int current_cabc_duty;
#endif
	struct pwm_device *pwm_bl;
	struct dsi_drv_cm_data shared_pdata;
	u32 pclk_rate;
	u32 byte_clk_rate;
	struct dss_module_power power_data;
	u32 dsi_irq_mask;
	struct mdss_hw *dsi_hw;
	struct mdss_panel_recovery *recovery;

	struct dsi_panel_cmds on_cmds;
	struct dsi_panel_cmds off_cmds;
	struct dsi_panel_cmds status_cmds;
	u32 status_value;
	struct dsi_panel_cmds ce_on_cmds;
	struct dsi_panel_cmds ce_off_cmds;
	struct dsi_panel_cmds cabc_on_cmds;
	struct dsi_panel_cmds cabc_off_cmds;
#if defined(CONFIG_CABC_TUNING_HX8394C)
	struct dsi_panel_cmds cabc_duty_72;
	struct dsi_panel_cmds cabc_duty_74;
	struct dsi_panel_cmds cabc_duty_78;
	struct dsi_panel_cmds cabc_duty_82;
#endif
	struct dsi_panel_cmds cabc_tune_cmds;
#if defined(CONFIG_FB_MSM_MDSS_CPT_QHD_PANEL)
	struct dsi_panel_cmds disp_on_cmd;
#endif

	struct dsi_panel_cmds video2cmd;
	struct dsi_panel_cmds cmd2video;

	int dsi_on_state;
	int dsi_off_state;

	struct dcs_cmd_list cmdlist;
	struct completion dma_comp;
	struct completion mdp_comp;
	struct completion video_comp;
	struct completion bta_comp;
	spinlock_t irq_lock;
	spinlock_t mdp_lock;
	int mdp_busy;
	struct mutex mutex;
	struct mutex cmd_mutex;
	struct mutex dfps_mutex;
	int mdp_tg_on;

	bool ulps;

	struct dsi_buf tx_buf;
	struct dsi_buf rx_buf;
	struct dsi_buf status_buf;
	int status_mode;
	int dsi_err_cnt;
#if defined(CONFIG_FB_MSM_MDSS_TC_DSI2LVDS_WXGA_PANEL)
	struct regulator *iovdd_vreg;
#endif
};

struct dsi_status_data {
	struct notifier_block fb_notifier;
	struct delayed_work check_status;
	struct msm_fb_data_type *mfd;
};

#if defined(CONFIG_FB_MSM_MDSS_MDP3)
enum {
	MIPI_RESUME_STATE,
	MIPI_SUSPEND_STATE,
};

struct mdss_dsi_driver_data {
	struct msm_fb_data_type *mfd;
	struct mdss_panel_data *pdata;
	struct mdss_dsi_ctrl_pdata *ctrl_pdata;
	struct mutex lock;
#if defined(CONFIG_LCD_CLASS_DEVICE)
	const char *panel_name;
#endif
#if defined(CONFIG_GET_LCD_ATTACHED)
	unsigned int manufacture_id;
	int lcd_attached;
#endif
};
#if defined(CONFIG_MDNIE_LITE_TUNING)
void mdss_dsi_cmds_send(struct mdss_dsi_ctrl_pdata *ctrl, struct dsi_cmd_desc *cmds, int cnt);
#endif
#endif /* CONFIG_FB_MSM_MDSS_MDP3 */

extern unsigned int gv_manufacture_id;
int dsi_panel_device_register(struct device_node *pan_node,
				struct mdss_dsi_ctrl_pdata *ctrl_pdata);

int mdss_dsi_cmds_tx(struct mdss_dsi_ctrl_pdata *ctrl,
		struct dsi_cmd_desc *cmds, int cnt);

int mdss_dsi_cmds_rx(struct mdss_dsi_ctrl_pdata *ctrl,
			struct dsi_cmd_desc *cmds, int rlen);

void mdss_dsi_host_init(struct mdss_panel_data *pdata);
void mdss_dsi_op_mode_config(int mode,
				struct mdss_panel_data *pdata);
void mdss_dsi_cmd_mode_ctrl(int enable);
void mdp4_dsi_cmd_trigger(void);
void mdss_dsi_cmd_mdp_start(struct mdss_dsi_ctrl_pdata *ctrl);
void mdss_dsi_cmd_bta_sw_trigger(struct mdss_panel_data *pdata);
void mdss_dsi_ack_err_status(struct mdss_dsi_ctrl_pdata *ctrl);
int mdss_dsi_clk_ctrl(struct mdss_dsi_ctrl_pdata *ctrl,
	u8 clk_type, int enable);
void mdss_dsi_clk_req(struct mdss_dsi_ctrl_pdata *ctrl,
				int enable);
void mdss_dsi_clk_ctrl_mdp(int ndx, int enable);
void mdss_dsi_controller_cfg(int enable,
				struct mdss_panel_data *pdata);
void mdss_dsi_sw_reset(struct mdss_panel_data *pdata);

irqreturn_t mdss_dsi_isr(int irq, void *ptr);
void mdss_dsi_irq_handler_config(struct mdss_dsi_ctrl_pdata *ctrl_pdata);

void mdss_dsi_set_tx_power_mode(int mode, struct mdss_panel_data *pdata);
int mdss_dsi_clk_div_config(struct mdss_panel_info *panel_info,
			    int frame_rate);
int mdss_dsi_clk_init(struct platform_device *pdev,
		      struct mdss_dsi_ctrl_pdata *ctrl_pdata);
void mdss_dsi_clk_deinit(struct mdss_dsi_ctrl_pdata *ctrl_pdata);
int mdss_dsi_enable_bus_clocks(struct mdss_dsi_ctrl_pdata *ctrl_pdata);
void mdss_dsi_disable_bus_clocks(struct mdss_dsi_ctrl_pdata *ctrl_pdata);
#if defined(CONFIG_FB_MSM_MDSS_MDP3)
int mdss_dsi_panel_reset(struct mdss_panel_data *pdata, int enable);
#else
void mdss_dsi_panel_reset(struct mdss_panel_data *pdata, int enable);
#endif
void mdss_dsi_phy_disable(struct mdss_dsi_ctrl_pdata *ctrl);
void mdss_dsi_phy_init(struct mdss_panel_data *pdata);
void mdss_dsi_phy_sw_reset(unsigned char *ctrl_base);
void mdss_dsi_cmd_test_pattern(struct mdss_dsi_ctrl_pdata *ctrl);
void mdss_dsi_video_test_pattern(struct mdss_dsi_ctrl_pdata *ctrl);
void mdss_dsi_panel_pwm_cfg(struct mdss_dsi_ctrl_pdata *ctrl);

int mdss_dsi_cmds_single_tx(struct mdss_dsi_ctrl_pdata *ctrl,
                 struct dsi_cmd_desc *cmds, int cnt);

void mdss_dsi_ctrl_init(struct mdss_dsi_ctrl_pdata *ctrl);
void mdss_dsi_cmd_mdp_busy(struct mdss_dsi_ctrl_pdata *ctrl);
void mdss_dsi_wait4video_done(struct mdss_dsi_ctrl_pdata *ctrl);
int mdss_dsi_cmdlist_commit(struct mdss_dsi_ctrl_pdata *ctrl, int from_mdp);
void mdss_dsi_cmdlist_kickoff(int intf);
int mdss_dsi_bta_status_check(struct mdss_dsi_ctrl_pdata *ctrl);
int mdss_dsi_reg_status_check(struct mdss_dsi_ctrl_pdata *ctrl);
bool __mdss_dsi_clk_enabled(struct mdss_dsi_ctrl_pdata *ctrl, u8 clk_type);

int mdss_dsi_panel_init(struct device_node *node,
		struct mdss_dsi_ctrl_pdata *ctrl_pdata,
		bool cmd_cfg_cont_splash);
int mdss_panel_get_dst_fmt(u32 bpp, char mipi_mode, u32 pixel_packing,
				char *dst_format);

int mdss_dsi_register_recovery_handler(struct mdss_dsi_ctrl_pdata *ctrl,
		struct mdss_panel_recovery *recovery);

static inline bool mdss_dsi_broadcast_mode_enabled(void)
{
	return ctrl_list[DSI_CTRL_MASTER]->shared_pdata.broadcast_enable &&
		ctrl_list[DSI_CTRL_SLAVE] &&
		ctrl_list[DSI_CTRL_SLAVE]->shared_pdata.broadcast_enable;
}

static inline struct mdss_dsi_ctrl_pdata *mdss_dsi_get_master_ctrl(void)
{
	if (mdss_dsi_broadcast_mode_enabled())
		return ctrl_list[DSI_CTRL_MASTER];
	else
		return NULL;
}

static inline struct mdss_dsi_ctrl_pdata *mdss_dsi_get_slave_ctrl(void)
{
	if (mdss_dsi_broadcast_mode_enabled())
		return ctrl_list[DSI_CTRL_SLAVE];
	else
		return NULL;
}

static inline bool mdss_dsi_is_master_ctrl(struct mdss_dsi_ctrl_pdata *ctrl)
{
	return mdss_dsi_broadcast_mode_enabled() &&
		(ctrl->ndx == DSI_CTRL_MASTER);
}

static inline bool mdss_dsi_is_slave_ctrl(struct mdss_dsi_ctrl_pdata *ctrl)
{
	return mdss_dsi_broadcast_mode_enabled() &&
		(ctrl->ndx == DSI_CTRL_SLAVE);
}

static inline struct mdss_dsi_ctrl_pdata *mdss_dsi_get_ctrl_by_index(int ndx)
{
	if (ndx >= DSI_CTRL_MAX)
		return NULL;

	return ctrl_list[ndx];
}
void mdss_dsi_mdp_busy_wait(int panel_ndx);
void mdss_dsi_dump_power_clk(struct mdss_panel_data *pdata, int flag);

/*for mondrian*/
void pwm_backlight_enable(void);
void pwm_backlight_disable(void);

#endif /* MDSS_DSI_H */
