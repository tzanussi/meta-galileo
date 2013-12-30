DESCRIPTION = "A small image just capable of allowing a device to boot."

IMAGE_INSTALL = "packagegroup-core-boot ${ROOTFS_PKGMANAGE_BOOTSTRAP} ${CORE_IMAGE_EXTRA_INSTALL}"

IMAGE_LINGUAS = " "

LICENSE = "GPLv2"

inherit core-image

IMAGE_FEATURES += "ssh-server-dropbear"

IMAGE_ROOTFS_SIZE = "512"
#IMAGE_EXTRA_SPACE = "20000"

IMAGE_INSTALL += "ethtool"

EXTRA_IMAGEDEPENDS = "grub-conf"

# net development packages, normally off
NET_DEV_INSTALL += "lwip-echo"
NET_DEV_INSTALL += "lwip-udp-echo"
#NET_DEV_INSTALL += "lwip-simhost"
NET_DEV_INSTALL += "sendraw"
NET_DEV_INSTALL += "recvraw"
# comment to add net dev packages
# NET_DEV_INSTALL = ""

IMAGE_DEV_INSTALL += "strace"
IMAGE_DEV_INSTALL += "openssh"
IMAGE_DEV_INSTALL += "kernel-modules"
IMAGE_DEV_INSTALL += "ppp"
IMAGE_DEV_INSTALL += "linuxptp"
IMAGE_DEV_INSTALL += "libstdc++"
# comment to add dev packages
IMAGE_DEV_INSTALL = ""

WIRELESS_INSTALL += "wireless-tools"
WIRELESS_INSTALL += "wpa-supplicant"
WIRELESS_INSTALL += "linux-firmware-iwlwifi-6000g2a-6"
WIRELESS_INSTALL += "linux-firmware-iwlwifi-135-6"
# comment to add wireless packages
WIRELESS_INSTALL = ""

#IMAGE_FSTYPES += "jffs2"

IMAGE_INSTALL += "${IMAGE_DEV_INSTALL} ${WIRELESS_INSTALL} ${NET_DEV_INSTALL}"
