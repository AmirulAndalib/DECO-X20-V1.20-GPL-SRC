#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=libssh
PKG_VERSION:=0.7.3
PKG_RELEASE=1

PKG_LICENSE:=LGPL-2.1+ BSD-2-Clause

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1
PKG_USE_MIPS16:=0

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libssh
  SECTION:=TP-LINK
  CATEGORY:=TP-LINK iplatform apps
  TITLE:=SSH library
  DEPENDS:=+libpthread +librt +zlib +libopenssl
  URL:=http://www.libssh.org/
  MAINTAINER:=Luka Perkov <luka@openwrt.org>
endef

define Package/libssh/description
 libssh is a mulitplatform C library implementing the SSHv2 and SSHv1 protocol
 for client and server implementations.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

CMAKE_OPTIONS = \
	-DCMAKE_INSTALL_PREFIX=/usr \
	-DCMAKE_BUILD_TYPE:STRING=Release \
	-DHAVE_STRTOULL=1 \
	-DHAVE_GETADDRINFO=1 \
	-DHAVE_TERMIOS_H=1 \
	-DWITH_EXAMPLES=OFF \
	-DWITH_GCRYPT=OFF \
	-DWITH_GSSAPI=OFF \
	-DWITH_LIBZ=ON \
	-DWITH_NACL=OFF \
	-DWITH_PCAP=OFF \
	-DWITH_SERVER=OFF \
	-DWITH_SFTP=OFF \
	-DWITH_SSH1=OFF \
	-DWITH_TESTING=OFF \

ifeq ($(CONFIG_BIG_ENDIAN),y)
CMAKE_OPTIONS += -DWITH_BIG_ENDIAN=ON
else
CMAKE_OPTIONS += -DWITH_BIG_ENDIAN=OFF
endif

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/libssh/
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/include/libssh/* \
		$(1)/usr/include/libssh/

	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libssh* \
		$(1)/usr/lib/

	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/pkgconfig/* \
		$(1)/usr/lib/pkgconfig/
endef

define Package/libssh/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) \
		$(PKG_INSTALL_DIR)/usr/lib/libssh* \
		$(1)/usr/lib/
endef

$(eval $(call BuildPackage,libssh))
