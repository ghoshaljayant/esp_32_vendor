#!/bin/bash
MY_PATH=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# check if ${VENODR_PACKAGE} is exported
# check if ${VENODR_PACKAGE} path exists
[[ ! -d $VENDOR_PACKAGE ]] && "ERROR: Please run esp_32_vendor/envsetup.sh" && return -1

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
  echo $package_path
  if [ "$1" = "-fullclean" ];then
    idf.py fullclean --project-dir $package_path
  fi
  idf.py build --project-dir $package_path
done

