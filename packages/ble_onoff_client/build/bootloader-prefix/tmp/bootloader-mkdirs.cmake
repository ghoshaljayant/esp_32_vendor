# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jayanta/esp/esp-idf/components/bootloader/subproject"
  "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader"
  "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix"
  "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix/tmp"
  "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix/src/bootloader-stamp"
  "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix/src"
  "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jayanta/esp/esp-idf/esp_32_vendor/packages/ble_onoff_client/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
