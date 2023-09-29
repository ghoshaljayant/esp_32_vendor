#!/bin/bash

args=$#
function print_help()
{
  echo
  echo "Usage:"
  echo
  echo " - source flash.sh [package_name]"
  echo " - source flash.sh -h"
  echo " - source flash.sh -list"
  echo
}

if [ $args = 0 ] || [ $1 = "-h" ];then
    print_help
    return 0
fi


SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
export MY_PATH=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

source $MY_PATH/tools.sh

# check if ${VENODR_PACKAGE} is exported
# check if ${VENODR_PACKAGE} path exists
[[ ! -d $VENDOR_PACKAGE ]] && "ERROR: VENDOR_PACKAGE Please run esp_32_vendor/envsetup.sh" && exit
[[ ! -n $DEVICE_PORT ]] && "ERROR: DEVICE_PORT Please run esp_32_vendor/envsetup.sh" && exit


detect_device

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

if [ "$ESP_DEVICE_COUNT" = "0" ];then
  echo "No device connected !!"
  return
fi



requested_package_path=("$VENDOR_PACKAGE/$1")
for package_path in "${package_path_array[@]}"
do

  if [ "$requested_package_path" = "$package_path" ];then

    cd $package_path
    if [ "$ESP_DEVICE_COUNT" = "1" ];then
      if [ "$2" = "-m" ];then
        echo ">> executing: idf.py -p $DEVICE_PORT flash monitor"
        idf.py -p $DEVICE_PORT flash monitor
      else
        echo ">> executing: idf.py -p $DEVICE_PORT flash"
        idf.py -p $DEVICE_PORT flash
      fi
    else

      list_device_port_by_index
      read -p 'enter the choice: ' device_port_index
      device_port=$(get_device_port_by_index $device_port_index)
      if [ "$2" = "-m" ];then
        echo ">> executing: idf.py -p $device_port flash monitor"
        idf.py -p $device_port flash monitor
      else
        echo ">> executing: idf.py -p $device_port flash"
        idf.py -p $device_port flash
      fi
    fi
    cd -
  fi
done