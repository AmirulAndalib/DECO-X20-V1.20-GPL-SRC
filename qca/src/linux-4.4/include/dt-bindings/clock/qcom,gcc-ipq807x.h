/*
 * Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _DT_BINDINGS_CLOCK_IPQ_GCC_807x_H
#define _DT_BINDINGS_CLOCK_IPQ_GCC_807x_H

#define GPLL0					1
#define UBI32_PLL				2
#define GPLL6					3
#define GPLL4					4
#define PCNOC_BFDCD_CLK_SRC			5
#define GPLL2					6
#define NSS_CRYPTO_PLL				7
#define NSS_PPE_CLK_SRC				8
#define GCC_XO_CLK_SRC				9
#define NSS_CE_CLK_SRC				10
#define NSS_NOC_BFDCD_CLK_SRC			11
#define GCC_SLEEP_CLK_SRC			12
#define APSS_AHB_CLK_SRC			13
#define NSS_PORT5_RX_CLK_SRC			14
#define NSS_PORT5_TX_CLK_SRC			15
#define PCIE0_AXI_CLK_SRC			16
#define PCIE1_AXI_CLK_SRC			17
#define USB0_MASTER_CLK_SRC			18
#define USB1_MASTER_CLK_SRC			19
#define APSS_AHB_POSTDIV_CLK_SRC		20
#define NSS_PORT1_RX_CLK_SRC			21
#define NSS_PORT1_TX_CLK_SRC			22
#define NSS_PORT2_RX_CLK_SRC			23
#define NSS_PORT2_TX_CLK_SRC			24
#define NSS_PORT3_RX_CLK_SRC			25
#define NSS_PORT3_TX_CLK_SRC			26
#define NSS_PORT4_RX_CLK_SRC			27
#define NSS_PORT4_TX_CLK_SRC			28
#define NSS_PORT5_RX_DIV_CLK_SRC		29
#define NSS_PORT5_TX_DIV_CLK_SRC		30
#define NSS_PORT6_RX_CLK_SRC			31
#define NSS_PORT6_TX_CLK_SRC			32
#define APSS_AXI_CLK_SRC			33
#define NSS_CRYPTO_CLK_SRC			34
#define NSS_PORT1_RX_DIV_CLK_SRC		35
#define NSS_PORT1_TX_DIV_CLK_SRC		36
#define NSS_PORT2_RX_DIV_CLK_SRC		37
#define NSS_PORT2_TX_DIV_CLK_SRC		38
#define NSS_PORT3_RX_DIV_CLK_SRC		39
#define NSS_PORT3_TX_DIV_CLK_SRC		40
#define NSS_PORT4_RX_DIV_CLK_SRC		41
#define NSS_PORT4_TX_DIV_CLK_SRC		42
#define NSS_PORT6_RX_DIV_CLK_SRC		43
#define NSS_PORT6_TX_DIV_CLK_SRC		44
#define NSS_UBI0_CLK_SRC			45
#define NSS_UBI1_CLK_SRC			46
#define UBI_MPT_CLK_SRC				47
#define BLSP1_QUP1_I2C_APPS_CLK_SRC		48
#define BLSP1_QUP1_SPI_APPS_CLK_SRC		49
#define BLSP1_QUP2_I2C_APPS_CLK_SRC		50
#define BLSP1_QUP2_SPI_APPS_CLK_SRC		51
#define BLSP1_QUP3_I2C_APPS_CLK_SRC		52
#define BLSP1_QUP3_SPI_APPS_CLK_SRC		53
#define BLSP1_QUP4_I2C_APPS_CLK_SRC		54
#define BLSP1_QUP4_SPI_APPS_CLK_SRC		55
#define BLSP1_QUP5_I2C_APPS_CLK_SRC		56
#define BLSP1_QUP5_SPI_APPS_CLK_SRC		57
#define BLSP1_QUP6_I2C_APPS_CLK_SRC		58
#define BLSP1_QUP6_SPI_APPS_CLK_SRC		59
#define BLSP1_UART1_APPS_CLK_SRC		60
#define BLSP1_UART2_APPS_CLK_SRC		61
#define BLSP1_UART3_APPS_CLK_SRC		62
#define BLSP1_UART4_APPS_CLK_SRC		63
#define BLSP1_UART5_APPS_CLK_SRC		64
#define BLSP1_UART6_APPS_CLK_SRC		65
#define CRYPTO_CLK_SRC				66
#define NSS_IMEM_CLK_SRC			67
#define NSS_UBI0_DIV_CLK_SRC			68
#define NSS_UBI1_DIV_CLK_SRC			69
#define PCIE0_AUX_CLK_SRC			70
#define PCIE0_PIPE_CLK_SRC			71
#define PCIE1_AUX_CLK_SRC			72
#define PCIE1_PIPE_CLK_SRC			73
#define SDCC1_APPS_CLK_SRC			74
#define SDCC2_APPS_CLK_SRC			75
#define USB0_AUX_CLK_SRC			76
#define USB0_MOCK_UTMI_CLK_SRC			77
#define USB0_PIPE_CLK_SRC			78
#define USB1_AUX_CLK_SRC			79
#define USB1_MOCK_UTMI_CLK_SRC			80
#define USB1_PIPE_CLK_SRC			81
#define GCC_APSS_AHB_CLK			82
#define GCC_APSS_AXI_CLK			83
#define GCC_BLSP1_AHB_CLK			84
#define GCC_BLSP1_QUP1_I2C_APPS_CLK		85
#define GCC_BLSP1_QUP1_SPI_APPS_CLK		86
#define GCC_BLSP1_QUP2_I2C_APPS_CLK		87
#define GCC_BLSP1_QUP2_SPI_APPS_CLK		88
#define GCC_BLSP1_QUP3_I2C_APPS_CLK		89
#define GCC_BLSP1_QUP3_SPI_APPS_CLK		90
#define GCC_BLSP1_QUP4_I2C_APPS_CLK		91
#define GCC_BLSP1_QUP4_SPI_APPS_CLK		92
#define GCC_BLSP1_QUP5_I2C_APPS_CLK		93
#define GCC_BLSP1_QUP5_SPI_APPS_CLK		94
#define GCC_BLSP1_QUP6_I2C_APPS_CLK		95
#define GCC_BLSP1_QUP6_SPI_APPS_CLK		96
#define GCC_BLSP1_UART1_APPS_CLK		97
#define GCC_BLSP1_UART2_APPS_CLK		98
#define GCC_BLSP1_UART3_APPS_CLK		99
#define GCC_BLSP1_UART4_APPS_CLK		100
#define GCC_BLSP1_UART5_APPS_CLK		101
#define GCC_BLSP1_UART6_APPS_CLK		102
#define GCC_CRYPTO_AHB_CLK			103
#define GCC_CRYPTO_AXI_CLK			104
#define GCC_CRYPTO_CLK				105
#define GCC_MEM_NOC_NSS_AXI_CLK			106
#define GCC_XO_CLK				107
#define GCC_XO_DIV4_CLK				108
#define GCC_MDIO_AHB_CLK			109
#define GCC_CRYPTO_PPE_CLK			110
#define GCC_NSS_CE_APB_CLK			111
#define GCC_NSS_CE_AXI_CLK			112
#define GCC_NSS_CFG_CLK				113
#define GCC_NSS_CRYPTO_CLK			114
#define GCC_NSS_CSR_CLK				115
#define GCC_NSS_EDMA_CFG_CLK			116
#define GCC_NSS_EDMA_CLK			117
#define GCC_NSS_IMEM_CLK			118
#define GCC_NSS_NOC_CLK				119
#define GCC_NSS_PORT1_RX_CLK			120
#define GCC_NSS_PORT1_TX_CLK			121
#define GCC_NSS_PORT2_RX_CLK			122
#define GCC_NSS_PORT2_TX_CLK			123
#define GCC_NSS_PORT3_RX_CLK			124
#define GCC_NSS_PORT3_TX_CLK			125
#define GCC_NSS_PORT4_RX_CLK			126
#define GCC_NSS_PORT4_TX_CLK			127
#define GCC_NSS_PORT5_RX_CLK			128
#define GCC_NSS_PORT5_TX_CLK			129
#define GCC_NSS_PORT6_RX_CLK			130
#define GCC_NSS_PORT6_TX_CLK			131
#define GCC_NSS_PPE_BTQ_CLK			132
#define GCC_NSS_PPE_CFG_CLK			133
#define GCC_NSS_PPE_CLK				134
#define GCC_NSS_PPE_IPE_CLK			135
#define GCC_NSS_PTP_REF_CLK			136
#define GCC_NSSNOC_CE_APB_CLK			137
#define GCC_NSSNOC_CE_AXI_CLK			138
#define GCC_NSSNOC_CRYPTO_CLK			139
#define GCC_NSSNOC_PPE_CFG_CLK			140
#define GCC_NSSNOC_PPE_CLK			141
#define GCC_NSSNOC_QOSGEN_REF_CLK		142
#define GCC_NSSNOC_TIMEOUT_REF_CLK		143
#define GCC_NSSNOC_UBI0_AHB_CLK			144
#define GCC_NSSNOC_UBI1_AHB_CLK			145
#define GCC_PORT1_MAC_CLK			146
#define GCC_PORT2_MAC_CLK			147
#define GCC_PORT3_MAC_CLK			148
#define GCC_PORT4_MAC_CLK			149
#define GCC_PORT5_MAC_CLK			150
#define GCC_PORT6_MAC_CLK			151
#define GCC_UBI0_AHB_CLK			152
#define GCC_UBI0_AXI_CLK			153
#define GCC_UBI0_CORE_CLK			154
#define GCC_UBI0_MPT_CLK			155
#define GCC_UBI1_AHB_CLK			156
#define GCC_UBI1_AXI_CLK			157
#define GCC_UBI1_CORE_CLK			158
#define GCC_UBI1_MPT_CLK			159
#define GCC_PCIE0_AHB_CLK			160
#define GCC_PCIE0_AUX_CLK			161
#define GCC_PCIE0_AXI_M_CLK			162
#define GCC_PCIE0_AXI_S_CLK			163
#define GCC_PCIE0_PIPE_CLK			164
#define GCC_PCIE1_AHB_CLK			165
#define GCC_PCIE1_AUX_CLK			166
#define GCC_PCIE1_AXI_M_CLK			167
#define GCC_PCIE1_AXI_S_CLK			168
#define GCC_PCIE1_PIPE_CLK			169
#define GCC_PRNG_AHB_CLK			170
#define GCC_QPIC_AHB_CLK			171
#define GCC_QPIC_CLK				172
#define GCC_SDCC1_AHB_CLK			173
#define GCC_SDCC1_APPS_CLK			174
#define GCC_SDCC2_AHB_CLK			175
#define GCC_SDCC2_APPS_CLK			176
#define GCC_UNIPHY0_AHB_CLK			177
#define GCC_UNIPHY0_PORT1_RX_CLK		178
#define GCC_UNIPHY0_PORT1_TX_CLK		179
#define GCC_UNIPHY0_PORT2_RX_CLK		180
#define GCC_UNIPHY0_PORT2_TX_CLK		181
#define GCC_UNIPHY0_PORT3_RX_CLK		182
#define GCC_UNIPHY0_PORT3_TX_CLK		183
#define GCC_UNIPHY0_PORT4_RX_CLK		184
#define GCC_UNIPHY0_PORT4_TX_CLK		185
#define GCC_UNIPHY0_PORT5_RX_CLK		186
#define GCC_UNIPHY0_PORT5_TX_CLK		187
#define GCC_UNIPHY0_SYS_CLK			188
#define GCC_UNIPHY1_AHB_CLK			189
#define GCC_UNIPHY1_PORT5_RX_CLK		190
#define GCC_UNIPHY1_PORT5_TX_CLK		191
#define GCC_UNIPHY1_SYS_CLK			192
#define GCC_UNIPHY2_AHB_CLK			193
#define GCC_UNIPHY2_PORT6_RX_CLK		194
#define GCC_UNIPHY2_PORT6_TX_CLK		195
#define GCC_UNIPHY2_SYS_CLK			196
#define GCC_USB0_AUX_CLK			197
#define GCC_USB0_MASTER_CLK			198
#define GCC_USB0_MOCK_UTMI_CLK			199
#define GCC_USB0_PHY_CFG_AHB_CLK		200
#define GCC_USB0_PIPE_CLK			201
#define GCC_USB0_SLEEP_CLK			202
#define GCC_USB1_AUX_CLK			203
#define GCC_USB1_MASTER_CLK			204
#define GCC_USB1_MOCK_UTMI_CLK			205
#define GCC_USB1_PHY_CFG_AHB_CLK		206
#define GCC_USB1_PIPE_CLK			207
#define GCC_USB1_SLEEP_CLK			208
#define AUDIO_PLL				209
#define GP1_CLK_SRC				210
#define GP2_CLK_SRC				211
#define GP3_CLK_SRC				212
#define GCC_GP1_CLK				213
#define GCC_GP2_CLK				214
#define GCC_GP3_CLK				215
#define SYSTEM_NOC_BFDCD_CLK_SRC		216
#define GCC_NSSNOC_SNOC_CLK			217
#define GCC_UBI0_NC_AXI_CLK			218
#define GCC_UBI1_NC_AXI_CLK			219
#define GPLL0_MAIN				220
#define UBI32_PLL_MAIN				221
#define GPLL6_MAIN				222
#define GPLL4_MAIN				223
#define GPLL2_MAIN				224
#define NSS_CRYPTO_PLL_MAIN			225
#define AUDIO_PLL_MAIN				226
#define GCC_CMN_12GPLL_AHB_CLK			227
#define GCC_CMN_12GPLL_SYS_CLK			228
#define GCC_SNOC_BUS_TIMEOUT2_AHB_CLK		229
#define GCC_SYS_NOC_USB0_AXI_CLK		230
#define GCC_SNOC_BUS_TIMEOUT3_AHB_CLK		231
#define GCC_SYS_NOC_USB1_AXI_CLK		232
#define GCC_SYS_NOC_PCIE0_AXI_CLK		233
#define GCC_SYS_NOC_PCIE1_AXI_CLK		234
#define QDSS_TSCTR_CLK_SRC			235
#define QDSS_AT_CLK_SRC				236
#define GCC_QDSS_AT_CLK				237
#define GCC_QDSS_DAP_CLK			238
#define ADSS_PWM_CLK_SRC			239
#define GCC_ADSS_PWM_CLK			240
#define SDCC1_ICE_CORE_CLK_SRC			241
#define GCC_SDCC1_ICE_CORE_CLK			242
#define GCC_DCC_CLK				243
#define PCIE0_RCHNG_CLK_SRC			244
#define GCC_PCIE0_AXI_S_BRIDGE_CLK		245
#define PCIE0_RCHNG_CLK				246
#define GCC_WCSSAON_RESET			89
#endif
