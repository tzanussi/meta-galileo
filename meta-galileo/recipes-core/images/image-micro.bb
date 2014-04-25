DESCRIPTION = "A small image just capable of allowing a device to boot."

IMAGE_INSTALL = "packagegroup-core-boot ${ROOTFS_PKGMANAGE_BOOTSTRAP} ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "GPLv2"

inherit core-image

IMAGE_INSTALL += "nostromo"

IMAGE_FEATURES += "ssh-server-dropbear"

IMAGE_ROOTFS_SIZE = "512"
#IMAGE_EXTRA_SPACE = "20000"

EXTRA_IMAGEDEPENDS = "grub-conf"

#IMAGE_FSTYPES += "jffs2"
