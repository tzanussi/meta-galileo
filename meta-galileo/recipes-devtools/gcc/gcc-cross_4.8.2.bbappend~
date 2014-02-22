#FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"

#SRC_URI += "file://0001-PR-driver-57651.patch"

EXTRA_OECONF_append_linux-yocto_micro = "--enable-lto \
                                         --with-plugin-ld=${STAGING_BINDIR_NATIVE}/${HOST_SYS}/${TARGET_PREFIX}ld \
					 --disable-nls \
					 --enable-languages=c,c++ \
					 --disable-libstdcxx-pch \
					 "
