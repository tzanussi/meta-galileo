DESCRIPTION = "A small image just capable of allowing a device to boot."

IMAGE_INSTALL = "packagegroup-core-boot ${ROOTFS_PKGMANAGE_BOOTSTRAP} ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "GPLv2"

inherit core-image

IMAGE_FEATURES += "ssh-server-dropbear"

IMAGE_ROOTFS_SIZE = "512"

IMAGE_INSTALL += "ethtool"

EXTRA_IMAGEDEPENDS = "grub-conf"

# development packages, normally off
IMAGE_DEV_INSTALL += "kernel-modules"
IMAGE_DEV_INSTALL += "strace"
IMAGE_DEV_INSTALL += "ppp"
IMAGE_DEV_INSTALL += "linuxptp"
IMAGE_DEV_INSTALL += "libstdc++"

IMAGE_DEV_INSTALL += "openssh"
IMAGE_DEV_INSTALL += "wireless-tools"
IMAGE_DEV_INSTALL += "wpa-supplicant"
IMAGE_DEV_INSTALL += "linux-firmware-iwlwifi-6000g2a-6"
IMAGE_DEV_INSTALL += "linux-firmware-iwlwifi-135-6"

#IMAGE_FSTYPES += "jffs2"

# uncomment to add dev packages
IMAGE_DEV_INSTALL = ""

IMAGE_INSTALL += "${IMAGE_DEV_INSTALL}"
