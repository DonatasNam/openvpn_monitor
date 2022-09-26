include $(TOPDIR)/rules.mk

PKG_NAME:=openvpn_monitor
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/openvpn_monitor
	DEPENDS:=+libubus +libubox +libblobmsg-json
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=Example program that interacts with ubus process
endef

define Package/openvpn_monitor/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openvpn_monitor $(1)/usr/bin
endef

$(eval $(call BuildPackage,openvpn_monitor))