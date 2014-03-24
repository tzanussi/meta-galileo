SUMMARY = "micro cgi - cgi 'scripts' written in C"
DESCRIPTION = "To be real men and avoid scripting runtime and libraries, we write our cgi scripts in C."
HOMEPAGE = "https://realmen-write-c.com"
SECTION = "net"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://catafile.c"

DEPENDS = "nostromo"

S = "${WORKDIR}"

do_compile() {
	     ${CC} catafile.c -o catafile
}

do_install() {
	     install -d ${D}${localstatedir}/nostromo/htdocs/cgi-bin
	     install -m 0755 catafile ${D}${localstatedir}/nostromo/htdocs/cgi-bin/catafile
}

FILES_${PN}-dbg += "${localstatedir}/nostromo/htdocs/cgi-bin/.debug"
