FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

PR := "${PR}.1"

KBRANCH = "standard/micro/galileo"

#SRC_URI = "git:///home/trz/yocto/micro/linux-yocto-micro-3.14.git;protocol=file;bareclone=1;branch=${KBRANCH},${KMETA},net-diet,lto;name=machine,meta,net-diet,lto"

# We want MICRO features for a micro build
KERNEL_FEATURES_MICRO = "cfg/perf-disable.scc \
                        cfg/acpi-disable.scc \
			cfg/block-disable.scc \
			cfg/pcie-disable.scc \
			cfg/mmc-disable.scc \
			cfg/mtd-disable.scc \
			cfg/nohz-disable.scc \
			cfg/misc-disable.scc \
			cfg/bug-disable.scc \
			cfg/printk-disable.scc \
			cfg/user-io-disable.scc \
			cfg/proc-sysctl-disable.scc \
			cfg/preempt-none.scc \
			cfg/crypto-disable.scc \
			cfg/hrt-disable.scc \
			cfg/x86-verbose-boot-disable.scc \
			cfg/slob.scc \
			features/net/diet.scc \
			cfg/net/ipv6-disable.scc \
			cfg/net/packet-disable.scc \
			cfg/proc-min-enable.scc \
			cfg/sysfs-disable.scc \
			cfg/splice-disable.scc \
			cfg/sysfs-syscall-disable.scc \
			cfg/uselib-disable.scc \
			cfg/pty-enable.scc \
			"

KERNEL_FEATURES_MICRO_TEST = "cfg/acpi-disable.scc \
			"

# Keep TRACING out unless we're tracing
# Turn on perf if enabling ftrace (compile problems)
# Also, stacktrace and hash triggers require frame pointers
KERNEL_FEATURES_TRACING = "cfg/perf-enable.scc \
			   cfg/printk-enable.scc \
			   cfg/bug-enable.scc \
			   cfg/frame-pointers-enable.scc \
			   features/ftrace/ftrace.scc \
			   cfg/kallsyms-enable.scc \
			   cfg/loglevel-debug.scc \
			   cfg/slub.scc \
			   cfg/slub-stats.scc \
			   features/lto/lto-disable.scc \
			   cfg/x86-verbose-boot-enable.scc \
			   "

# We want LTO for a micro build
# Turn ftrace off if using lto
KERNEL_FEATURES_LTO = "features/ftrace/ftrace-disable.scc \
		      features/lto/lto.scc \
		      "

# We don't want these NET features for a micro build
# Add NET only if you really need to; we normally
# want them off to save space and networking should work
# fine without them
KERNEL_FEATURES_NET = "cfg/net/ip-ping.scc \
		      cfg/net/tcp-metrics.scc \
		      cfg/net/ethtool.scc \
		      cfg/net/lpf-filter.scc \
		      cfg/net/rtnetlink.scc \
		      cfg/net/ip-offload.scc \
		      cfg/net/mib-stats.scc\
		      cfg/net/tcp-fastopen.scc \
		      cfg/net/inet-raw.scc \
		      cfg/net/packet-mmap.scc \
		      cfg/net/fib-list.scc \
		      "

# These are things we use for lwip builds
KERNEL_FEATURES_LWIP = "cfg/inet-disable.scc"

# These are things we use for netless builds
KERNEL_FEATURES_NONET = "cfg/net-disable.scc"

# micro
KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_MICRO} \
                                  ${KERNEL_FEATURES_LTO} \
                                  "

# micro - no lto
#KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_MICRO} \
#                                  "

# micro test
#KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_MICRO} \
#			           ${KERNEL_FEATURES_LTO} \
#			           cfg/slub.scc \
#			           cfg/slub-stats.scc \
#			           cfg/net/inet-raw.scc \
#			           "

# lwip
#KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_MICRO} \
#    			           ${KERNEL_FEATURES_LWIP} \
#			           ${KERNEL_FEATURES_LTO} \
#			           "

# nonet
#KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_MICRO} \
#			           ${KERNEL_FEATURES_NONET} \
#			           ${KERNEL_FEATURES_LTO} \
#			           "

# tracing
#KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_MICRO_TEST} \
#                                   ${KERNEL_FEATURES_TRACING} \
#                                   "

# tracing-full
#KERNEL_FEATURES_append_galileo += "${KERNEL_FEATURES_TRACING} \
#                                   "

SRCREV_machine_${MACHINE}="${AUTOREV}"
SRCREV_meta="${AUTOREV}"
SRCREV_net-diet="${AUTOREV}"
SRCREV_lto="${AUTOREV}"
LOCALCOUNT = "0"

COMPATIBLE_MACHINE_ = "galileo"

RDEPENDS_kernel-base=""

# uncomment and replace these SRCREVs with the real commit ids once you've had
# the appropriate changes committed to the upstream linux-yocto repo
#SRCREV_machine_pn-linux-yocto-tiny_galileo ?= "840bb8c059418c4753415df56c9aff1c0d5354c8"
#SRCREV_meta_pn-linux-yocto-tiny_galileo ?= "4fd76cc4f33e0afd8f906b1e8f231b6d13b6c993"
#LINUX_VERSION = "3.10.9"
