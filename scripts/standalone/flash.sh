#!/bin/bash

args=$#
function print_help()
{
  echo
  echo "Usage:"
  echo
  echo " - source flash.sh [path][package_name][device_name]"
  echo " - source flash.sh -h"
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


echo "$1"
# run idf.py -p $DEVICE_PORT flash

if [ "$ESP_DEVICE_COUNT" = "0" ];then
  echo "No device connected !!"
  return
fi



cd $package_path
if [ "$ESP_DEVICE_COUNT" = "1" ];then

else

  list_device_port_by_index
  read -p 'enter the choice: ' device_port_index
  device_port=$(get_device_port_by_index $device_port_index)
  
fi

if [ "$2" = "-m" ];then
  echo ">> executing: idf.py -p $device_port flash monitor"
  idf.py -p $device_port flash monitor
else
  echo ">> executing: idf.py -p $device_port flash"
  idf.py -p $device_port flash
fi

cd -