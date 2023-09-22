# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS $ENV{VENDOR_PACKAGE}/ble_onoff_client/components/button
                         $ENV{VENDOR_PACKAGE}/ble_onoff_client/components/example_init
                         $ENV{VENDOR_PACKAGE}/ble_onoff_client/components/example_nvs)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(onoff_client)
