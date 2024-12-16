SUMMARY = "Showing current time on SSD1306"
DESCRIPTION = "${SUMMARY}"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=12f884d2ae1ff87c09e5b7ccc2c4ca7e"


SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "currenttime.service"

SRC_URI = "file://Makefile \
           file://currenttime.c \
           file://COPYING \
           file://currenttime.service \
           "        

RDEPENDS:${PN} = "bash"
FILES:${PN} += "${systemd_unitdir}/system/currenttime.service"

S = "${WORKDIR}"

do_compile() {
    cd ${S}
    oe_runmake
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/currenttime ${D}${bindir}

    install -d ${D}/${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/currenttime.service ${D}/${systemd_unitdir}/system

#    install -d ${D}${sysconfdir}/init.d
#    install -m 0755 ${WORKDIR}/currenttime.sh ${D}${sysconfdir}/init.d/currenttime.sh
}

# INITSCRIPT_NAME = "currenttime.sh"
# INITSCRIPT_PARAMS = "defaults"
inherit systemd
# inherit update-rc.d

