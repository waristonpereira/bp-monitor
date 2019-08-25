#
# Build and install Blood Pressure Libs
# @autor Wariston Pereira <waristonfernando@gmail.com>
#
BP_MONITOR_VERSION = 0.1
BP_MONITOR_SITE = .
BP_MONITOR_METHOD = local
BP_MONITOR_OVERRIDE_SRCDIR = ../bp-monitor/src/
BP_MONITOR_INSTALL_STAGING = YES

define BP_MONITOR_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define BP_MONITOR_INSTALL_STAGING_CMDS
    $(INSTALL) -D -m 0755 $(@D)/libbpmonitor.so $(STAGING_DIR)/usr/lib
    $(INSTALL) -D -m 0755 $(@D)/include/bp-monitor.h $(STAGING_DIR)/usr/include
endef

define BP_MONITOR_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/libbpmonitor.so $(TARGET_DIR)/usr/lib
	$(INSTALL) -D -m 0755 $(@D)/include/bp-monitor.h $(TARGET_DIR)/usr/include
endef

$(eval $(generic-package))
