FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PR := "${PR}.1"

KBRANCH = "standard/micro/galileo"

SRC_URI = "git:///home/trz/yocto/micro-test/linux-yocto-micro-3-13.git;protocol=file;bareclone=1;branch=${KBRANCH},${KMETA},net-diet;name=machine,meta,net-diet"

KERNEL_FEATURES_append_galileo += " cfg/perf-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/acpi-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/block-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/pcie-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/mmc-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/mtd-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/nohz-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/misc-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/slob.scc"
#KERNEL_FEATURES_append_galileo += " cfg/bug-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/printk-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/user-io-disable.scc"

#KERNEL_FEATURES_append_galileo += " cfg/inet-disable.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net-disable.scc"

KERNEL_FEATURES_append_galileo += " cfg/kallsyms-enable.scc"
KERNEL_FEATURES_append_galileo += " cfg/loglevel-debug.scc"
KERNEL_FEATURES_append_galileo += " cfg/slub.scc"
KERNEL_FEATURES_append_galileo += " cfg/slub-stats.scc"
KERNEL_FEATURES_append_galileo += " cfg/gpio-user.scc"

KERNEL_FEATURES_append_galileo += " features/net/diet.scc"

#KERNEL_FEATURES_append_galileo += " cfg/net/ip-ping.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net/tcp-metrics.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net/ethtool.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net/lpf-filter.scc"
KERNEL_FEATURES_append_galileo += " cfg/net/rtnetlink.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net/ip-offload.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net/mib-stats.scc"
#KERNEL_FEATURES_append_galileo += " cfg/net/tcp-fastopen.scc"
KERNEL_FEATURES_append_galileo += " cfg/net/inet-raw.scc"

SRCREV_machine_${MACHINE}="${AUTOREV}"
SRCREV_meta="${AUTOREV}"
SRCREV_net-diet="${AUTOREV}"
LOCALCOUNT = "0"

COMPATIBLE_MACHINE_ = "galileo"

RDEPENDS_kernel-base=""

# uncomment and replace these SRCREVs with the real commit ids once you've had
# the appropriate changes committed to the upstream linux-yocto repo
#SRCREV_machine_pn-linux-yocto-tiny_galileo ?= "840bb8c059418c4753415df56c9aff1c0d5354c8"
#SRCREV_meta_pn-linux-yocto-tiny_galileo ?= "4fd76cc4f33e0afd8f906b1e8f231b6d13b6c993"
#LINUX_VERSION = "3.10.9"
