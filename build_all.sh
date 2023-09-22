#!/bin/bash
if [ "$1" = "-h" ];then
    echo "source build_all.sh [--clean]"
    echo "source build_all.sh -h"
    return 0
fi

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

# run idf.py build
for package_path in "${package_path_array[@]}"
do

  if [ -n "${IDF_BUILD_TARGET}" ];then
    echo ">> executing: idf.py set-target $IDF_BUILD_TARGET --project-dir $package_path"
    cd $package_path && idf.py set-target $IDF_BUILD_TARGET && cd -
  fi

  if [ "$1" = "--clean" ];then
    echo ">> executing: idf.py fullclean --project-dir $package_path"
    idf.py fullclean --project-dir $package_path
  fi
  echo ">> executing: idf.py build --project-dir $package_path"
  idf.py build --project-dir $package_path
done

