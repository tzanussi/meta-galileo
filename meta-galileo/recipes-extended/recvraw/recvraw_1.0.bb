SUMMARY = "net test - simplest possible ethernet frame receive"
DESCRIPTION = "Code from Blog entry 'Receiving raw packets in linux without pcap (http://austinmarton.wordpress.com/2012/06/03/receiving-raw-packets-in-linux-without-pcap/)"
HOMEPAGE = "https://gist.github.com/austinmarton/2862515"
SECTION = "net"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://recvRawEth.c"

S = "${WORKDIR}"

do_compile() {
	     ${CC} recvRawEth.c -o recvraw
}

do_install() {
	     install -d ${D}${bindir}
	     install -m 0755 recvraw ${D}${bindir}
}
