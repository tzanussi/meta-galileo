require lwip.inc

S = "${WORKDIR}"

SRC_URI += "file://udp-echo.c \
	file://udp-echo.h \
	file://lwipopts.h \
	file://main.c \
	file://packetdump.c \
	file://packetdump.h \
	file://Makefile \
	file://packetif.c \
	file://packetif.h \
	file://README \
	file://timer.c \
	file://timer.h \
	file://ports/unix/include/arch/perf.h \
	file://ports/unix/include/arch/sys_arch.h \
	file://ports/unix/include/arch/cc.h \
	file://ports/unix/sys_arch.c \
"

EXTRA_OEMAKE = "\
    'ARCH=linux' \
    'CC=${CC}' \
    'CFLAGS=${CFLAGS} -g -Wall -pedantic -D$(ARCH) -DIPv4 -Os -fpack-struct \
	-I$(LWIPDIR)/include -I$(LWIPARCH)/include -I$(LWIPDIR)/include/ipv4 \
	-I$(LWIPDIR)/include/ipv6 -I. -DLWIP_DEBUG -DETHARP_DEBUG' \
"

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 ${WORKDIR}/udp-echop ${D}${bindir}
}
