#
# Copyright (C) 2009-2013 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=xtables-addons
ifeq ($(strip $(call CompareKernelPatchVer,$(KERNEL_PATCHVER),ge,3.7.0)),1)
PKG_VERSION:=2.3
PKG_RELEASE:=1
PKG_MD5SUM:=7d942729c365a549513511061f74c3e3
else
PKG_VERSION:=1.45
PKG_RELEASE:=3
PKG_MD5SUM:=802d2f556a5e545f44e4b69937bf8490
PATCH_DIR:=./patches-1.x
endif

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=@SF/xtables-addons
PKG_BUILD_DEPENDS:=iptables
PKG_INSTALL:=1
PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=Jo-Philipp Wich <jow@openwrt.org>

PKG_FIXUP:=autoreconf

include $(INCLUDE_DIR)/package.mk

define Package/xtables-addons
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  SUBMENU:=xtables-addons
  TITLE:=Extensions not distributed in the main Xtables
  URL:=http://xtables-addons.sourceforge.net/
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

# uses GNU configure

CONFIGURE_ARGS+= \
	--with-kbuild="$(LINUX_DIR)" \
	--with-xtables="$(STAGING_DIR)/usr" \
	--with-xtlibdir="/usr/lib/iptables" \

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		ARCH="$(LINUX_KARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		DEPMOD="/bin/true" \
		all
endef

define Build/Install
	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(LINUX_KARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		DESTDIR="$(PKG_INSTALL_DIR)" \
		DEPMOD="/bin/true" \
		install
endef

# 1: extension/module suffix used in package name
# 2: extension/module display name used in package title/description
# 3: list of extensions to package
# 4: list of modules to package
# 5: module load priority
# 6: module depends
define BuildTemplate

 ifneq ($(3),)
  define Package/iptables-mod-$(1)
    $$(call Package/xtables-addons)
    TITLE:=$(2) iptables extension
    DEPENDS:=iptables $(if $(4),+kmod-ipt-$(1))
  endef

  define Package/iptables-mod-$(1)/install
	$(INSTALL_DIR) $$(1)/usr/lib/iptables
	for m in $(3); do \
		$(CP) \
			$(PKG_INSTALL_DIR)/usr/lib/iptables/lib$$$$$$$${m}.so \
			$$(1)/usr/lib/iptables/ ; \
	done
  endef

  $$(eval $$(call BuildPackage,iptables-mod-$(1)))
 endif

 ifneq ($(4),)
  define KernelPackage/ipt-$(1)
    $$(call Package/xtables-addons)
    TITLE:=$(2) netfilter module
    DEPENDS:=+kmod-ipt-core $(5)
    KCONFIG:=$(6)
    FILES:=$(foreach mod,$(4),$(PKG_BUILD_DIR)/extensions/$(mod).$(LINUX_KMOD_SUFFIX))
    AUTOLOAD:=$(call AutoProbe,$(notdir $(4)))
  endef

  $$(eval $$(call KernelPackage,ipt-$(1)))
 endif

endef


define Package/iptaccount
  $(call Package/xtables-addons)
  TITLE:=iptables-mod-account control utility
  DEPENDS:=iptables +iptables-mod-account
endef

define Package/iptaccount/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/sbin
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libxt_ACCOUNT_cl.so* \
		$(1)/usr/lib/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/sbin/iptaccount \
		$(1)/usr/sbin/
endef


#$(eval $(call BuildTemplate,SUFFIX,DESCRIPTION,EXTENSION,MODULE,PRIORITY,DEPENDS))

$(eval $(call BuildTemplate,compat-xtables,API compatibilty layer,,compat_xtables,+IPV6:kmod-ip6tables,CONFIG_NF_CONNTRACK_MARK=y))
$(eval $(call BuildTemplate,rawpost,RAWPOST,,iptable_rawpost $(if $(CONFIG_IPV6),ip6table_rawpost),+kmod-ipt-compat-xtables +IPV6:kmod-ip6tables))
$(eval $(call BuildTemplate,nathelper-rtsp,RTSP Conntrack and NAT,,rtsp/nf_conntrack_rtsp rtsp/nf_nat_rtsp,+kmod-ipt-conntrack-extra +kmod-ipt-nat))

$(eval $(call BuildTemplate,pctl,pctl,xt_pctl,xt_pctl,))
$(eval $(call BuildTemplate,account,ACCOUNT,xt_ACCOUNT,ACCOUNT/xt_ACCOUNT,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,chaos,CHAOS,xt_CHAOS,xt_CHAOS,+kmod-ipt-compat-xtables +kmod-ipt-delude +kmod-ipt-tarpit))
$(eval $(call BuildTemplate,condition,Condition,xt_condition,xt_condition,))
$(eval $(call BuildTemplate,delude,DELUDE,xt_DELUDE,xt_DELUDE,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,dhcpmac,DHCPMAC,xt_DHCPMAC,xt_DHCPMAC,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,dnetmap,DNETMAP,xt_DNETMAP,xt_DNETMAP,+kmod-ipt-compat-xtables +kmod-ipt-nat))
$(eval $(call BuildTemplate,fuzzy,fuzzy,xt_fuzzy,xt_fuzzy,))
$(eval $(call BuildTemplate,geoip,geoip,xt_geoip,xt_geoip,))
$(eval $(call BuildTemplate,iface,iface,xt_iface,xt_iface,))
$(eval $(call BuildTemplate,ipmark,IPMARK,xt_IPMARK,xt_IPMARK,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,ipp2p,IPP2P,xt_ipp2p,xt_ipp2p,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,ipv4options,ipv4options,xt_ipv4options,xt_ipv4options,))
$(eval $(call BuildTemplate,length2,length2,xt_length2,xt_length2,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,logmark,LOGMARK,xt_LOGMARK,xt_LOGMARK,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,lscan,lscan,xt_lscan,xt_lscan,))
$(eval $(call BuildTemplate,lua,Lua PacketScript,xt_LUA,LUA/xt_LUA,+kmod-ipt-conntrack-extra))
$(eval $(call BuildTemplate,psd,psd,xt_psd,xt_psd,))
$(eval $(call BuildTemplate,quota2,quota2,xt_quota2,xt_quota2,))
$(eval $(call BuildTemplate,rawnat,RAWNAT,xt_RAWDNAT xt_RAWSNAT,xt_RAWNAT,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,steal,STEAL,xt_STEAL,xt_STEAL,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,sysrq,SYSRQ,xt_SYSRQ,xt_SYSRQ,+kmod-ipt-compat-xtables))
$(eval $(call BuildTemplate,tarpit,TARPIT,xt_TARPIT,xt_TARPIT,+kmod-ipt-compat-xtables +IPV6:kmod-ipv6))

$(eval $(call BuildPackage,iptaccount))
