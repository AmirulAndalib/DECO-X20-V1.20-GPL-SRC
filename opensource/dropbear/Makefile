#
# Copyright (C) 2006-2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dropbear
PKG_VERSION:=2015.67
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:= \
	http://matt.ucc.asn.au/dropbear/releases/ \
	https://dropbear.nl/mirror/releases/
PKG_MD5SUM:=e967e320344cd4bfebe321e3ab8514d6

PKG_LICENSE:=MIT
PKG_LICENSE_FILES:=LICENSE libtomcrypt/LICENSE libtommath/LICENSE

PKG_BUILD_PARALLEL:=1
PKG_USE_MIPS16:=0

PKG_CONFIG_DEPENDS:=CONFIG_DROPBEAR_ECC

include $(INCLUDE_DIR)/package.mk

define Package/dropbear/Default
  URL:=http://matt.ucc.asn.au/dropbear/
  DEPENDS:=+libuci
endef

define Package/dropbear/config
	source "$(SOURCE)/Config.in"
endef

define Package/dropbear
  $(call Package/dropbear/Default)
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  TITLE:=Small SSH2 client/server
endef

define Package/dropbear/description
 A small SSH2 server/client designed for small memory environments.
endef

define Package/dropbear/conffiles
/etc/dropbear/dropbear_rsa_host_key
/etc/dropbear/dropbear_dss_host_key
/etc/config/dropbear
endef

define Package/dropbearconvert
  $(call Package/dropbear/Default)
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  TITLE:=Utility for converting SSH keys
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

CONFIGURE_ARGS += \
	--disable-pam \
	--enable-openpty \
	--enable-syslog \
	$(if $(CONFIG_SHADOW_PASSWORDS),,--disable-shadow) \
	--disable-lastlog \
	--disable-utmp \
	--disable-utmpx \
	--disable-wtmp \
	--disable-wtmpx \
	--disable-loginfunc \
	--disable-pututline \
	--disable-pututxline \
	--disable-zlib \
	--enable-bundled-libtom

TARGET_CFLAGS += -DARGTYPE=3 -ffunction-sections -fdata-sections
TARGET_LDFLAGS += -luci -Wl,--gc-sections

define Build/Configure
	$(Build/Configure/Default)

	# Enforce that all replacements are made, otherwise options.h has changed
	# format and this logic is broken.
	for OPTION in DROPBEAR_ECDSA DROPBEAR_ECDH DROPBEAR_CURVE25519; do \
	  awk 'BEGIN { rc = 1 } \
	       /'$$$$OPTION'/ { $$$$0 = "$(if $(CONFIG_DROPBEAR_ECC),,// )#define '$$$$OPTION'"; rc = 0 } \
	       { print } \
	       END { exit(rc) }' $(PKG_BUILD_DIR)/options.h \
	       >$(PKG_BUILD_DIR)/options.h.new && \
	  mv $(PKG_BUILD_DIR)/options.h.new $(PKG_BUILD_DIR)/options.h || exit 1; \
	done
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		PROGRAMS="dropbear dbclient dropbearkey scp" \
		MULTI=1 SCPPROGRESS=1
	+$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		PROGRAMS="dropbearconvert"
endef

define Package/dropbear/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbearmulti $(1)/usr/sbin/dropbear
	$(INSTALL_DIR) $(1)/usr/bin
	$(LN) ../sbin/dropbear $(1)/usr/bin/scp
	$(LN) ../sbin/dropbear $(1)/usr/bin/ssh
	$(LN) ../sbin/dropbear $(1)/usr/bin/dbclient
	$(LN) ../sbin/dropbear $(1)/usr/bin/dropbearkey
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DATA) ./files/dropbear.config $(1)/etc/config/dropbear
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/dropbear.init $(1)/etc/init.d/dropbear
	$(call init_order,$(1)/etc/init.d/dropbear)
	$(INSTALL_DIR) $(1)/usr/lib/opkg/info
	$(INSTALL_DIR) $(1)/etc/dropbear
	touch $(1)/etc/dropbear/dropbear_rsa_host_key
endef

define Package/dropbearconvert/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbearconvert $(1)/usr/bin/dropbearconvert
endef

$(eval $(call BuildPackage,dropbear))
$(eval $(call BuildPackage,dropbearconvert))
