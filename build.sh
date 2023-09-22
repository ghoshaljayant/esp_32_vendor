#!/bin/bash

if [ "$1" = "-h" ];then
    echo "source build.sh [package_name] [--clean]"
    echo "source build.sh -h"
    return 0
fi

MY_PATH=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
source "$MY_PATH"/export.sh
# check if ${VENODR_PACKAGE} is exported
# check if ${VENODR_PACKAGE} path exists
[[ ! -d $VENDOR_PACKAGE ]] && "ERROR: Please run esp_32_vendor/export.sh"

# list all pacakges under ${VENODR_PACKAGE}
package_array=()
package_array_string=$(ls $VENDOR_PACKAGE)
package_array=($package_array_string)
package_path_array=()
for package in "${package_array[@]}"
do
  package_path_array+=("$VENDOR_PACKAGE/$package")
done
echo ${package_path_array[@]}

# run idf.py build
for package_path in "${package_path_array[@]}"
do

  if [ "$1" = "$package_path" ];then
    echo $package_path
    if [ "$2" = "--clean" ];then
        idf.py fullclean --project-dir $package_path
    fi
    idf.py build --project-dir $package_path
  fi
done