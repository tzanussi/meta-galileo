FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://lsusb-iconv.patch"

EXTRA_OECONF += " --without-iconv"
