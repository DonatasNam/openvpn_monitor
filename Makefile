include $(TOPDIR)/rules.mk

PKG_NAME:=openvpn_monitor
PKG_VERSION:=1.0.0
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/openvpn_monitor
	DEPENDS:=+libubus +libubox +libblobmsg-json +libargp
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=Example program that interacts with ubus process
endef

define Package/openvpn_monitor/install
	$(INSTALL_DIR) $(1)/usr/bin $(1)/etc/init.d $(1)/etc/config 
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openvpn_monitor $(1)/usr/bin
	$(INSTALL_BIN) ./files/openvpn_monitor.init $(1)/etc/init.d/openvpn_monitor
	$(INSTALL_CONF) ./files/openvpn_monitor.conf $(1)/etc/config/openvpn_monitor
endef

$(eval $(call BuildPackage,openvpn_monitor))