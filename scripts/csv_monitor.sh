#! /bin/bash

if [ "$1" = "-h" ];then
  echo "source csv_parser.sh target_name"
  return 0
fi

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
export MY_PATH=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

csv_file_path="$VENDOR_HOME/targets/$1.csv"

if [ ! -f "$csv_file_path" ];then
  echo "Invalid target name: $1"
  return -1
fi

echo "Valid target name: $1"

# check if any device is connected or not
source $MY_PATH/tools.sh
detect_device
if [ "$ESP_DEVICE_COUNT" = "0" ];then
  echo "No device connected !!"
  return -1
fi


path_list=()
index=0
while IFS="," read -r path package_name
do
  echo "$index) $package_name"
  path_list+=($path)
  (( index++ ))   
done < <(tail -n +2 $csv_file_path)

read -p 'enter the choice: ' device_port_index
device_port=$(get_device_port_by_index $device_port_index)
echo "device port: $device_port"

path=$(eval echo "${path_list[$device_port_index]}")
cd $path
idf.py -p $device_port monitor
