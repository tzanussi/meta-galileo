SUMMARY = "net test - simplest possible ethernet frame send"
DESCRIPTION = "Code from Blog entry 'Sending raw Ethernet packets from \
a specific interface in C on Linux (austinmarton.wordpress.com/2011/09/14/sending-raw-ethernet-packets-from-a-specific-interface-in-c-on-linux/)"
HOMEPAGE = "https://gist.github.com/austinmarton/1922600"
SECTION = "net"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://sendRawEth.c"

S = "${WORKDIR}"

do_compile() {
	     ${CC} sendRawEth.c -o sendraw
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 sendraw ${D}${bindir}
}
