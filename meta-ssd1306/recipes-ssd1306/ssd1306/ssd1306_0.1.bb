SUMMARY = "SSD1306 Display Driver"
DESCRIPTION = "${SUMMARY}"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "ssd1306.service"
inherit module
inherit systemd

SRC_URI = "file://Makefile \
           file://ssd1306temp.c \
           file://digitRenderer \
           file://i2cSend \
           file://COPYING \
           file://ssd1306_load.sh \
           file://ssd1306.service \
          "

S = "${WORKDIR}"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES:${PN} += "kernel-module-ssd1306temp"
FILES:${PN} += "${sysconfdir}/init.d/ssd1306_load.sh \
                ${systemd_unitdir}/system/ssd1306.service"

do_configure() {
    export KDIR="${STAGING_KERNEL_DIR}"
    cd ${S}
    oe_runmake KDIR=${KDIR}
}

do_compile() {
    export KDIR="${STAGING_KERNEL_DIR}"
    oe_runmake KDIR=${KDIR}
}

do_install() {
    install -d ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra
    install -m 0644 ${B}/ssd1306temp_dev.ko ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra

    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/ssd1306_load.sh ${D}${sysconfdir}/init.d

    install -d ${D}/${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/ssd1306.service ${D}/${systemd_unitdir}/system
}
