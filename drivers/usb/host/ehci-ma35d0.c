// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2020 Nuvoton Technology Corp.
 *
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <log.h>
#include <malloc.h>
#include <usb.h>
#include <usb/ehci-ci.h>
#include <asm/io.h>

#include <dt-bindings/clock/ma35d0-clk.h>
#include <syscon.h>
#include <regmap.h>
#include <ma35d0-sys.h>

#include "ehci.h"

#if !CONFIG_IS_ENABLED(DM_USB)
#error "CONFIG_DM_USB must be enabled!!"
#endif

/* Declare global data pointer */
DECLARE_GLOBAL_DATA_PTR;

struct ma35d0_ehci_priv {
	struct ehci_ctrl ctrl;
	struct usb_ehci *ehci;
	struct regmap	*sysreg;
	void __iomem	*reg;
	struct clk	clk;
};

static int ehci_ma35d0_probe(struct udevice *dev)
{
	struct ma35d0_ehci_priv *ma35d0_ehci = dev_get_priv(dev);
	struct ofnode_phandle_args args;
	fdt_addr_t hcd_base;
	struct ehci_hccr *hccr;
	struct ehci_hcor *hcor;
	u32 reg, timeout = (500 / 20);
	int ret;

	/*
	 *  enable clock
	 */
	ret = clk_get_by_index(dev, 0, &ma35d0_ehci->clk);
	if (ret < 0) {
		dev_err(dev, "%s failed: %d\n", __func__, ret);
		return ret;
	}

	ret = clk_enable(&ma35d0_ehci->clk);
	if (ret != 0) {
		dev_err(dev, "%s clk_enable() failed: %d\n", __func__, ret);
		return ret;
	}

	/* get system register map */
	ret = dev_read_phandle_with_args(dev, "nuvoton,sys", NULL,
					 0, 0, &args);
	if (ret) {
		dev_err(dev, "Failed to get syscon: %d\n", ret);
		return ret;
	}

	ma35d0_ehci->sysreg = syscon_node_to_regmap(args.node);
	if (IS_ERR(ma35d0_ehci->sysreg)) {
		ret = PTR_ERR(ma35d0_ehci->sysreg);
		dev_err(dev, "can't get syscon: %d\n", ret);
		return ret;
	}

	/* USBPMISCR; HSUSBH0 & HSUSBH1 PHY */
	regmap_read(ma35d0_ehci->sysreg, REG_SYS_USBPMISCR, &reg);
	if ((reg & 0x20302) != 0x20302) {
		reg = (reg & ~0x30003) | 0x20002;
		regmap_write(ma35d0_ehci->sysreg, REG_SYS_USBPMISCR, reg);
		do {
			mdelay(20);
			regmap_read(ma35d0_ehci->sysreg, REG_SYS_USBPMISCR, &reg);
		} while (((reg & 0x20302) != 0x20302) && (timeout-- > 0));
	}
	dev_dbg(&pdev->dev, "REG_SYS_USBPMISCR = 0x%x, timeout = %d\n", reg, timeout);

	/* set UHOVRCURH(SYS_MISCFCR0[12]) 1 => USBH Host over-current detect is high-active */
	/*                                 0 => USBH Host over-current detect is low-active  */
	regmap_read(ma35d0_ehci->sysreg, REG_SYS_MISCFCR0, &reg);
	regmap_write(ma35d0_ehci->sysreg, REG_SYS_MISCFCR0, (reg & ~(1 << 12)));

	/*
	 * Get the base address for EHCI controller from the device node
	 */
	hcd_base = devfdt_get_addr(dev);
	if (hcd_base == FDT_ADDR_T_NONE) {
		debug("Can't get the EHCI register base address\n");
		return -ENXIO;
	}

	hccr = (struct ehci_hccr *)hcd_base;
	hcor = (struct ehci_hcor *)
		((u64)hccr + HC_LENGTH(ehci_readl(&hccr->cr_capbase)));

	return ehci_register(dev, hccr, hcor, NULL, 0, USB_INIT_HOST);
}

int ehci_ma35d0_deregister(struct udevice *dev)
{
	/* we cannot shutdown ehci phy, that will cause ohci halt */
	return 0;
}

static const struct udevice_id ehci_ma35d0_ids[] = {
	{ .compatible = "nuvoton,ma35d0-ehci0" },
	{ .compatible = "nuvoton,ma35d0-ehci1" },
	{ }
};

U_BOOT_DRIVER(usb_ehci) = {
	.name	= "ma35d0_ehci",
	.id	= UCLASS_USB,
	.of_match = ehci_ma35d0_ids,
	.probe = ehci_ma35d0_probe,
	.remove = ehci_ma35d0_deregister,
	.ops	= &ehci_usb_ops,
	.platdata_auto_alloc_size = sizeof(struct usb_platdata),
	.priv_auto_alloc_size = sizeof(struct ma35d0_ehci_priv),
	.flags	= DM_FLAG_ALLOC_PRIV_DMA,
};
