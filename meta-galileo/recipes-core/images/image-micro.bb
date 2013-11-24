DESCRIPTION = "A small image just capable of allowing a device to boot."

IMAGE_INSTALL = "packagegroup-core-boot ${ROOTFS_PKGMANAGE_BOOTSTRAP} ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "GPLv2"

inherit core-image

IMAGE_FSTYPES = "${INITRAMFS_TYPES}"
IMAGE_ROOTFS_SIZE = "2048"
EXTRA_IMAGECMD_append_ext2 = " -N 2000"

IMAGE_FEATURES += "package-management"
IMAGE_FEATURES += "ssh-server-dropbear"
#ROOTFS_POSTPROCESS_COMMAND += "remove_packaging_data_files ; "

IMAGE_INSTALL += "kernel-modules"
IMAGE_INSTALL += "ethtool"
IMAGE_INSTALL += "strace"
IMAGE_INSTALL += "ppp"
IMAGE_INSTALL += "linuxptp"
IMAGE_INSTALL += "libstdc++"

EXTRA_IMAGEDEPENDS = "grub-conf"

IMAGE_DEV_INSTALL += "openssh"
IMAGE_DEV_INSTALL += "wireless-tools"
IMAGE_DEV_INSTALL += "wpa-supplicant"
IMAGE_DEV_INSTALL += "linux-firmware-iwlwifi-6000g2a-6"
IMAGE_DEV_INSTALL += "linux-firmware-iwlwifi-135-6"

# uncomment to add dev packages
IMAGE_DEV_INSTALL = ""

IMAGE_INSTALL += "${IMAGE_DEV_INSTALL}"
