#! /bin/bash

old_pwd=$(pwd)
echo "$old_pwd"

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

source $CSV_SCRIPT_PATH/csv_init_.sh
csv_init

path_list=()
index=0
while IFS="," read -r path package_name
do
  echo "$index) $package_name"

  # $ESP_IDF_HOME OR $VENDOR_HOME
  vend_path=$(echo "$path" | sed -e "s|ROOT|${VENDOR_HOME}|g")
  esp_path=$(echo $path | sed -e "s|ROOT|${ESP_IDF_HOME}|g")

  if [ -d "$vend_path" ]; then
    path=$vend_path
  elif [ -d "$esp_path" ]; then
    path=$esp_path
  fi

  path_list+=($path)
  (( index++ ))
  if [ $index = $ESP_DEVICE_COUNT ];then
    break
  fi
done < <(tail -n +2 $csv_file_path)

read -p 'enter the choice: ' device_port_index
device_port=$(get_device_port_by_index $device_port_index)
echo "device port: $device_port"

path=$(eval echo "${path_list[$device_port_index]}")
cd $path
idf.py -p $device_port monitor --timestamps


cd $old_pwd