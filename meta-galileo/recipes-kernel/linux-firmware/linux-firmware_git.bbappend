do_install_append() {
        install -m 0644 LICENCE.iwlwifi_firmware ${D}/lib/firmware
        install -m 0644 iwlwifi-6000g2a-6.ucode ${D}/lib/firmware
        install -m 0644 iwlwifi-135-6.ucode ${D}/lib/firmware
}

PACKAGES =+ "${PN}-iwlwifi-6000g2a-6 \
             ${PN}-iwlwifi-135-6"


RDEPENDS_${PN}-iwlwifi-6000g2a-6 = "${PN}-iwlwifi-license"
RDEPENDS_${PN}-iwlwifi-135-6 = "${PN}-iwlwifi-license"

FILES_${PN}-iwlwifi-license =   "/lib/firmware/LICENCE.iwlwifi_firmware"
FILES_${PN}-rtl-license =       "/lib/firmware/LICENCE.rtlwifi_firmware.txt"
FILES_${PN}-iwlwifi-6000g2a-6 = "/lib/firmware/iwlwifi-6000g2a-6.ucode"
FILES_${PN}-iwlwifi-135-6 =     "/lib/firmware/iwlwifi-135-6.ucode"
