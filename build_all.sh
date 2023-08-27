
# check if ${VENODR_PACKAGES} is exported
# check if ${VENODR_PACKAGES} path exists
echo "$VENDOR_PACKAGES"
[[ ! -f $VENDOR_PACKAGES ]] && "ERROR: Please run esp_32_vendor/export.sh"
# list all pacakges under ${VENODR_PACKAGES}
# under each package locate first CMakeLists.txt
# run idf.py build


