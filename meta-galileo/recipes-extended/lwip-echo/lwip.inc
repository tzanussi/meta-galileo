SUMMARY = "lwIP - A Lightweight TCP/IP stack"
DESCRIPTION = "lwIP is a small independent implementation of the TCP/IP protocol suite that has been initially developed by Adam Dunkels.  The focus of the lwIP TCP/IP implementation is to reduce resource usage while still having a full scale TCP. This makes lwIP suitable for use in embedded systems with tens of kilobytes of free RAM and room for around 40 kilobytes of code ROM."
HOMEPAGE = "http://savannah.nongnu.org/projects/lwip/"
BUGTRACKER = "http://savannah.nongnu.org/bugs/?group=lwip"
SECTION = "libs"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://git/COPYING;md5=59a383b05013356e0c9899b06dc5da3f \
	 file://git/src/core/udp.c;beginline=8;endline=35;md5=576e9990e2a25bfd3c9cdb067390456d \
	 "

SRC_URI = "git://git.savannah.nongnu.org/lwip.git;name=libgit \
          "

SRCREV_libgit = "ae300c98a4107458d0aa040c074d89ee9d3ac984"
