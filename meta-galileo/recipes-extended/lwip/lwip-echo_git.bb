require lwip.inc

S = "${WORKDIR}"

SRC_URI += "file://echo.c \
	file://echo.h \
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
	file://apps/snmp_private_mib/lwip_prvmib.c \
	file://apps/snmp_private_mib/private_mib.h \
	file://ports/unix/include/arch/perf.h \
	file://ports/unix/include/arch/sys_arch.h \
	file://ports/unix/include/arch/cc.h \
	file://ports/unix/include/netif \
	file://ports/unix/include/netif/tunif.h \
	file://ports/unix/include/netif/delif.h \
	file://ports/unix/include/netif/pcapif.h \
	file://ports/unix/include/netif/fifo.h \
	file://ports/unix/include/netif/dropif.h \
	file://ports/unix/include/netif/unixif.h \
	file://ports/unix/include/netif/tapif.h \
	file://ports/unix/include/netif/sio.h \
	file://ports/unix/include/netif/tcpdump.h \
	file://ports/unix/include/netif/list.h \
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
	     install -m 0755 ${WORKDIR}/echop ${D}${bindir}
}
