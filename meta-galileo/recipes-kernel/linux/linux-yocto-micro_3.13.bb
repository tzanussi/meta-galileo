require recipes-kernel/linux/linux-yocto.inc

# We need lzma (as CONFIG_KERNEL_LZMA=y)
DEPENDS += "xz-native"

KBRANCH_DEFAULT = "standard/micro/base"
KBRANCH = "${KBRANCH_DEFAULT}"

LINUX_KERNEL_TYPE = "micro"
KCONFIG_MODE = "--allnoconfig"

LINUX_VERSION ?= "3.13"

KMETA = "meta"

SRCREV_machine ?= "f20047520a57322f05d95a18a5fbd082fb15cb87"
SRCREV_meta ?= "cb96851e7e559f9247d616d08406db6135c357cb"

PR = "${INC_PR}.1"
PV = "${LINUX_VERSION}+git${SRCPV}"

SRC_URI = "git://git.yoctoproject.org/linux-yocto-dev.git;bareclone=1;branch=${KBRANCH},meta;name=machine,meta"

COMPATIBLE_MACHINE = "(qemux86)"

# Functionality flags
KERNEL_FEATURES = ""

EXTRA_OEMAKE = "LD=${STAGING_BINDIR_NATIVE}/${HOST_SYS}/${TARGET_PREFIX}ld AR=${STAGING_BINDIR_NATIVE}/${HOST_SYS}/${TARGET_PREFIX}gcc-ar"
