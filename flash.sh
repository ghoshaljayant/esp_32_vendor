#!/bin/bash

if [ "$1" = "-h" ];then
    echo "source flash.sh [package_name]"
    echo "source flash.sh -h"
    echo "source flash.sh -list"
    return 0
fi

MY_PATH=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# check if ${VENODR_PACKAGE} is exported
# check if ${VENODR_PACKAGE} path exists
[[ ! -d $VENDOR_PACKAGE ]] && "ERROR: Please run esp_32_vendor/envsetup.sh" && return -1
[[ -n $DEVICE_PORT ]] && "ERROR: Please run esp_32_vendor/envsetup.sh" && return -1

# list all pacakges under ${VENODR_PACKAGE}
package_array=()
package_array_string=$(ls $VENDOR_PACKAGE)
package_array=($package_array_string)

if [ "$1" = "-list" ];then
    for package in "${package_array[@]}"
    do
        echo "$package"
    done
return 0
fi

package_path_array=()
for package in "${package_array[@]}"
do
  package_path_array+=("$VENDOR_PACKAGE/$package")
done
echo "$1"
# run idf.py -p $DEVICE_PORT flash
requested_package_path=("$VENDOR_PACKAGE/$1")
for package_path in "${package_path_array[@]}"
do

  if [ "$requested_package_path" = "$package_path" ];then

    cd $package_path
    echo ">> executing: idf.py -p $DEVICE_PORT flash"
    idf.py -p $DEVICE_PORT flash
    cd -
    
  fi
done