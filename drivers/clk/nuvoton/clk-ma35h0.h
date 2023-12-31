// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Nuvoton technology corporation
 * All rights reserved.
 */

#ifndef __DRIVERS_CLK_NUVOTON_CLK_MA35H0_H
#define __DRIVERS_CLK_NUVOTON_CLK_MA35H0_H

#include <linux/clk-provider.h>


#define UNKNOWN_U8_DATA 	0xFF
#define UNKNOWN_TYPE_HZ		0xFFFFFFFF
#define UNKNOWN_HZ   		0xFFFFFFFF
#define UNKNOWN_DATA 		0xFFFFFFFF


#define BITMASK_1 		0x01
#define BITMASK_2 		0x03
#define BITMASK_3 		0x07
#define BITMASK_4 		0x0F

#define UNKNOWN_GATE_ID 	clk_max
#define UNKNOWN_MUX_ID		0x0C
#define UNKNOWN_DIV_ID		0x04

#define	TYPE_HXT_HZ		0
#define	TYPE_LXT_HZ		1
#define	TYPE_HIRC_HZ		2
#define	TYPE_LIRC_HZ		3
#define	TYPE_CAPLL_HZ		4
#define	TYPE_SYSPLL_HZ		5
#define	TYPE_DDRPLL_HZ		6
#define	TYPE_APLL_HZ		7
#define	TYPE_EPLL_HZ		8
#define	TYPE_VPLL_HZ		9
#define	TYPE_CAPLL_DIV2_HZ	10
#define	TYPE_CAPLL_DIV4_HZ	11
#define	TYPE_EPLL_DIV2_HZ	12
#define	TYPE_EPLL_DIV4_HZ	13
#define	TYPE_VPLL_DIV2_HZ	14
#define	TYPE_CA35_HZ		15
#define	TYPE_AXI0_ACLK_HZ	16
#define	TYPE_SYSCLK0_HZ		17
#define	TYPE_SYSCLK1_HZ		18
#define	TYPE_SYSCLK1_DIV2_HZ	19
#define	TYPE_HCLK0_HZ		20
#define	TYPE_HCLK1_HZ		21
#define	TYPE_HCLK2_HZ		22
#define	TYPE_HCLK3_HZ		23
#define	TYPE_PCLK0_HZ		24
#define	TYPE_PCLK1_HZ		25
#define	TYPE_PCLK2_HZ		26
#define	TYPE_PCLK3_HZ		27
#define	TYPE_PCLK4_HZ		28
#define	TYPE_PCLK3_DIV_4096_HZ	29
#define	TYPE_PCLK4_DIV_4096_HZ	30
#define	TYPE_USBPHY0_HZ		31
#define	TYPE_USBPHY1_HZ		32
#define	TYPE_HZ_MAX		33

/* VSI-PLL Specification limits */
#define VSIPLL_FREF_MAX_FREQ	200000000UL
#define VSIPLL_FREF_MIN_FREQ	1000000UL

#define VSIPLL_FREFDIVM_MAX_FREQ	40000000UL
#define VSIPLL_FREFDIVM_MIN_FREQ0	1000000UL
#define VSIPLL_FREFDIVM_MIN_FREQ1	10000000UL

#define VSIPLL_FCLK_MAX_FREQ		2400000000UL
#define VSIPLL_FCLK_MIN_FREQ		600000000UL

#define VSIPLL_FCLKO_MAX_FREQ		2400000000UL
#define VSIPLL_FCLKO_MIN_FREQ		85700000UL

#define VSIPLL_SPREAD_RANGE		194
#define VSIPLL_MODULATION_FREQ		50000

struct __ma35h0_clk_sel_type_map {
	u32 muxMap[4];
};

struct __ma35h0_clk_gate_data {
	u32 type;
	ulong rate;
	u32 offst;
	u32 bitIdx;
	u32 bitWidth;
};

struct __ma35h0_clk_mux_data {
	u32 offst;
	u32 bitIdx;
	u32 bitWidth;
	ulong muxMap[16];
};

struct __ma35h0_clk_div_data {
	u32 offst;
	u32 bitIdx;
	u32 bitWidth;
	u8 divMap[8];
};

struct ___ma35h0_clk_reg_info {
	struct __ma35h0_clk_gate_data clkGate;
	struct __ma35h0_clk_mux_data  clkMux;
	struct __ma35h0_clk_div_data  clkDiv;
};


enum ma35h0_pll_type {
	MA35H0_CAPLL,
	MA35H0_DDRPLL,
	MA35H0_APLL,
	MA35H0_EPLL,
	MA35H0_VPLL,
};

enum ma35h0_pll_mode {
	VSIPLL_INTEGER_MODE,
	VSIPLL_FRACTIONAL_MODE,
	VSIPLL_SS_MODE,
};

struct __ma35h0_pll_data {
	u8 type;
	u8 mode;
	unsigned long rate;
	u8 ctl0;
	u8 ctl1;
	u8 ctl2;
};

struct vsipll_freq_conf_reg_tbl {
	unsigned long freq;
	u8 mode;
	u32 ctl0_reg;
	u32 ctl1_reg;
	u32 ctl2_reg;
};

struct __ma35h0_clk_data {
	void *base;
	struct clk parent_hxt;
	struct clk parent_lxt;
	struct clk parent_hirc;
	struct clk parent_lirc;
	struct clk parent_usbphy0;
	struct clk parent_usbphy1;
};

static struct __ma35h0_clk_sel_type_map __clk_sel_type_tbl[] = {
/* ca35clk_mux	48*/	{{TYPE_HXT_HZ, TYPE_CAPLL_HZ, TYPE_DDRPLL_HZ, UNKNOWN_TYPE_HZ}},
/* sysclk0_mux	49*/	{{TYPE_EPLL_DIV2_HZ, TYPE_SYSPLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* sysclk1_mux	50*/	{{TYPE_HXT_HZ, TYPE_SYSPLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* sdh0_mux	51*/	{{TYPE_SYSPLL_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* sdh1_mux	52*/	{{TYPE_SYSPLL_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* dcu_mux	53*/	{{TYPE_EPLL_DIV2_HZ, TYPE_SYSPLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* spi0_mux	54*/	{{TYPE_PCLK1_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* spi1_mux	55*/	{{TYPE_PCLK2_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* spi2_mux	56*/	{{TYPE_PCLK1_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* spi3_mux	57*/	{{TYPE_PCLK2_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* qspi0_mux 	58*/	{{TYPE_PCLK0_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* qspi1_mux 	59*/	{{TYPE_PCLK0_HZ, TYPE_APLL_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
/* UNKNOWN	*/	{{UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ, UNKNOWN_TYPE_HZ}},
};

static struct __ma35h0_pll_data __ma35h0_capll_data = {
	.type = 0,
	.ctl0= REG_CLK_PLL0CTL0,
};


static struct __ma35h0_pll_data __ma35h0_ddrpll_data = {
	.type = 1,
	.ctl0= REG_CLK_PLL2CTL0,
	.ctl1= REG_CLK_PLL2CTL1,
	.ctl2= REG_CLK_PLL2CTL2,
};

static struct __ma35h0_pll_data __ma35h0_apll_data = {
	.type = 2,
	.ctl0= REG_CLK_PLL3CTL0,
	.ctl1= REG_CLK_PLL3CTL1,
	.ctl2= REG_CLK_PLL3CTL2,
};

static struct __ma35h0_pll_data __ma35h0_epll_data = {
	.type = 3,
	.ctl0= REG_CLK_PLL4CTL0,
	.ctl1= REG_CLK_PLL4CTL1,
	.ctl2= REG_CLK_PLL4CTL2,
};

static struct __ma35h0_pll_data __ma35h0_vpll_data = {
	.type = 4,
	.ctl0= REG_CLK_PLL5CTL0,
	.ctl1= REG_CLK_PLL5CTL1,
	.ctl2= REG_CLK_PLL5CTL2,
};

static struct __ma35h0_clk_gate_data __clk_id_gate_sets[] = {
/* capll	0 */  	{TYPE_CAPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* ddrpll	1 */  	{TYPE_DDRPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* apll		2 */  	{TYPE_APLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* epll		3 */  	{TYPE_EPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* vpll		4 */  	{TYPE_VPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* hxt_gate	5 */  	{TYPE_HXT_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* lxt_gate	6 */  	{TYPE_LXT_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_LXTEN_Pos, 1},
/* hirc_gate	7 */  	{TYPE_HIRC_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HIRCEN_Pos, 1},
/* lirc_gate	8 */  	{TYPE_LIRC_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_LIRCEN_Pos, 1},
/* ddr0_gate	9 */  	{TYPE_DDRPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_CA35CKEN_Pos, 1},
/* ddr6_gate	10*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_CA35CKEN_Pos, 1},
/* sdh0_gate	11*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_SDH0CKEN_Pos, 1},
/* sdh1_gate	12*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_SDH1CKEN_Pos, 1},
/* nand_gate	13*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_NANDCKEN_Pos, 1},
/* usbh_gate	14*/  	{TYPE_USBPHY0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_USBHCKEN_Pos, 1},
/* husbh0_gate	15*/  	{TYPE_USBPHY0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_HUSBH0EN_Pos, 1},
/* husbh1_gate	16*/  	{TYPE_USBPHY1_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_HUSBH1EN_Pos, 1},
/* dcu_gate	17*/  	{TYPE_EPLL_DIV2_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_DCUCKEN_Pos, 1},
/* emac0_gate	18*/  	{TYPE_EPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_GMAC0CKEN_Pos, 1},
/* emac1_gate	19*/  	{TYPE_EPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_GMAC1CKEN_Pos, 1},
/* rtc_gate	20*/  	{TYPE_LXT_HZ, UNKNOWN_HZ, REG_CLK_APBCLK0, CLK_APBCLK0_RTCCKEN_Pos, 1},
/* ddr_gate	21*/  	{TYPE_DDRPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK0, CLK_APBCLK0_DDRPCKEN_Pos, 1},
/* i2c0_gate	22*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_I2C0CKEN_Pos, 1},
/* i2c1_gate	23*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_I2C1CKEN_Pos, 1},
/* i2c2_gate	24*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_I2C2CKEN_Pos, 1},
/* i2c3_gate	25*/	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_I2C3CKEN_Pos, 1},
/* i2c4_gate	26*/	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_I2C4CKEN_Pos, 1},
/* i2c5_gate	27*/	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_I2C5CKEN_Pos, 1},
/* qspi0_gate	28*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_QSPI0CKEN_Pos, 1},
/* qspi1_gate	29*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_QSPI1CKEN_Pos, 1},
/* spi0_gate	30*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK2, CLK_APBCLK2_SPI0CKEN_Pos, 1},
/* spi1_gate	31*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK2, CLK_APBCLK2_SPI1CKEN_Pos, 1},
/* spi2_gate	32*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK2, CLK_APBCLK2_SPI2CKEN_Pos, 1},
/* spi3_gate	33*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_APBCLK2, CLK_APBCLK2_SPI3CKEN_Pos, 1},
/* gpa_gate	34*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPACKEN_Pos, 1},
/* gpb_gate	35*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPBCKEN_Pos, 1},
/* gpc_gate	36*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPCCKEN_Pos, 1},
/* gpd_gate	37*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPDCKEN_Pos, 1},
/* gpe_gate	38*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPECKEN_Pos, 1},
/* gpf_gate	39*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPFCKEN_Pos, 1},
/* gpg_gate	40*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPGCKEN_Pos, 1},
/* gph_gate	41*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPHCKEN_Pos, 1},
/* gpi_gate	42*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPICKEN_Pos, 1},
/* gpj_gate	43*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPJCKEN_Pos, 1},
/* gpk_gate	44*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPKCKEN_Pos, 1},
/* gpl_gate	45*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPLCKEN_Pos, 1},
/* gpm_gate	46*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPMCKEN_Pos, 1},
/* gpn_gate	47*/  	{TYPE_HCLK0_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK1, CLK_SYSCLK1_GPNCKEN_Pos, 1},
/* ca35clk_mux	48*/  	{TYPE_CAPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_CA35CKEN_Pos, 1},
/* sysclk0_mux	49*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* sysclk1_mux	50*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* sdh0_mux	51*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_SDH0CKEN_Pos, 1},
/* sdh1_mux	52*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_SYSCLK0, CLK_SYSCLK0_SDH1CKEN_Pos, 1},
/* dcu_mux	53*/  	{TYPE_EPLL_DIV2_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* spi0_mux	54*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* spi1_mux	55*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* spi2_mux	56*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* spi3_mux	57*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* qspi0_mux	58*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* qspi1_mux	59*/  	{TYPE_SYSPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* dcup_div	60*/  	{TYPE_VPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* emac0_div	61*/  	{TYPE_EPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* emac1_div	62*/  	{TYPE_EPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* aclk0_div	63*/  	{TYPE_CAPLL_HZ, UNKNOWN_HZ, REG_CLK_PWRCTL, CLK_PWRCTL_HXTEN_Pos, 1},
/* wdt1_gate	64*/  	{TYPE_LIRC_HZ, UNKNOWN_HZ, REG_CLK_APBCLK1, CLK_APBCLK1_WDT1CKEN_Pos, 1},
/* UNKNOWN clk_max*/  	{UNKNOWN_TYPE_HZ, UNKNOWN_HZ, UNKNOWN_DATA, UNKNOWN_DATA, UNKNOWN_DATA},
};

static struct __ma35h0_clk_mux_data __clk_id_mux_sets[] = {
/* ca35clk_mux	48*/  	{REG_CLK_CLKSEL0, CLK_CLKSEL0_CA35CKSEL_Pos, 2,{TYPE_HXT_HZ, TYPE_CAPLL_HZ, TYPE_DDRPLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* sysclk0_mux	49*/  	{REG_CLK_CLKSEL0, CLK_CLKSEL0_SYSCK0SEL_Pos, 1,{TYPE_EPLL_DIV2_HZ, TYPE_SYSPLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* sysclk1_mux	50*/  	{REG_CLK_CLKSEL0, CLK_CLKSEL0_SYSCK1SEL_Pos, 2,{TYPE_HXT_HZ, TYPE_SYSPLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* sdh0_mux	51*/  	{REG_CLK_CLKSEL0, CLK_CLKSEL0_SD0SEL_Pos,    2,{TYPE_SYSPLL_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* sdh1_mux	52*/  	{REG_CLK_CLKSEL0, CLK_CLKSEL0_SD1SEL_Pos,    2,{TYPE_SYSPLL_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* dcu_mux	53*/  	{REG_CLK_CLKSEL0, CLK_CLKSEL0_DCUSEL_Pos,    1,{TYPE_EPLL_DIV2_HZ, TYPE_SYSPLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* spi0_mux	54*/  	{REG_CLK_CLKSEL4, CLK_CLKSEL4_SPI0SEL_Pos,   2,{TYPE_PCLK1_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* spi1_mux	55*/  	{REG_CLK_CLKSEL4, CLK_CLKSEL4_SPI1SEL_Pos,   2,{TYPE_PCLK2_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* spi2_mux	56*/  	{REG_CLK_CLKSEL4, CLK_CLKSEL4_SPI2SEL_Pos,   2,{TYPE_PCLK1_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* spi3_mux	57*/  	{REG_CLK_CLKSEL4, CLK_CLKSEL4_SPI3SEL_Pos,   2,{TYPE_PCLK2_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* qspi0_mux	58*/  	{REG_CLK_CLKSEL4, CLK_CLKSEL4_QSPI0SEL_Pos,  2,{TYPE_PCLK0_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* qspi1_mux	59*/  	{REG_CLK_CLKSEL4, CLK_CLKSEL4_QSPI1SEL_Pos,  2,{TYPE_PCLK0_HZ, TYPE_APLL_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
/* UNKNOWN_MUX_ID*/  	{UNKNOWN_DATA, UNKNOWN_DATA, UNKNOWN_DATA,{UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ, UNKNOWN_HZ}},
};

static struct __ma35h0_clk_div_data __clk_id_div_sets[] = {
/* dcup_div	60*/  	{REG_CLK_CLKDIV0, CLK_CLKDIV0_DCUPDIV_Pos,  3, {2, 4, 6, 8, 10, 12, 14, 16}},
/* emac0_div	61*/  	{REG_CLK_CLKDIV0, CLK_CLKDIV0_EMAC0DIV_Pos, 2, {2, 2, 100, 10, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA}},
/* emac1_div	62*/  	{REG_CLK_CLKDIV0, CLK_CLKDIV0_EMAC1DIV_Pos, 2, {2, 2, 100, 10, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA}},
/* aclk0_div	63*/  	{REG_CLK_CLKDIV0, CLK_CLKDIV0_ACLK0DIV_Pos, 1, {2, 4, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA}},
/* UNKNOWN_DIV_ID */  	{UNKNOWN_DATA, UNKNOWN_DATA, UNKNOWN_DATA, {UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA, UNKNOWN_U8_DATA}},
};


#endif
