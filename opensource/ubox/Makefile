include $(TOPDIR)/rules.mk

PKG_NAME:=ubox
PKG_VERSION:=2014-03-27
PKG_RELEASE=$(PKG_SOURCE_VERSION)

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://nbd.name/luci2/ubox.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=1d9d2e6ae99c9ba72d1bc40e554d5f422c9b9196
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
CMAKE_INSTALL:=1

PKG_LICENSE:=GPLv2
PKG_LICENSE_FILES:=

PKG_MAINTAINER:=John Crispin <blogic@openwrt.org>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

TARGET_LDFLAGS += $(if $(CONFIG_USE_EGLIBC),-lrt)

define Package/ubox
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  DEPENDS:=+libubox +ubusd +ubus +libuci +USE_EGLIBC:librt
  TITLE:=OpenWrt system helper toolbox
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

#$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{kmodloader,logd,logread,validate_data} $(1)/sbin/
define Package/ubox/install
	$(INSTALL_DIR) $(1)/sbin $(1)/usr/sbin $(1)/lib/ $(1)/etc/init.d/

	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/usr/sbin/{kmodloader,logd,logread,validate_data} $(1)/sbin/
	$(INSTALL_BIN) ./filesystem/log.init $(1)/etc/init.d/log
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/lib/libvalidate.so $(1)/lib

	ln -s /sbin/kmodloader $(1)/usr/sbin/rmmod
	ln -s /sbin/kmodloader $(1)/usr/sbin/insmod
	ln -s /sbin/kmodloader $(1)/usr/sbin/lsmod
	ln -s /sbin/kmodloader $(1)/usr/sbin/modinfo
	ln -s /sbin/kmodloader $(1)/usr/sbin/modprobe
endef

$(eval $(call BuildPackage,ubox))
