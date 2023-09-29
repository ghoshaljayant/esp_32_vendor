#!/bin/bash

if [ "$1" = "-h" ];then
    echo "source lunch.sh [target_name][target_index]"
    echo "source lunch.sh -h"
    echo "source lunch.sh"
    return 0
fi

MY_PATH=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# check if ${VENODR_PACKAGE} is exported
# check if ${VENODR_PACKAGE} path exists
[[ ! -d $VENDOR_PACKAGE ]] && "ERROR: Please run esp_32_vendor/envsetup.sh" && return -1

