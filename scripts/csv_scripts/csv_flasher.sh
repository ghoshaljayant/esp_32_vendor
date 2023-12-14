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

index=0
while IFS="," read -r path package_name
do
  path=$(eval echo "$path")
  # $ESP_IDF_HOME OR $VENDOR_HOME
  vend_path=$(echo "$path" | sed -e "s|ROOT|${VENDOR_HOME}|g")
  esp_path=$(echo $path | sed -e "s|ROOT|${ESP_IDF_HOME}|g")

  if [ -d "$vend_path" ]; then
    echo "$vend_path found."
    path=$vend_path
  elif [ -d "$esp_path" ]; then
    echo "$esp_path found."
    path=$esp_path
  fi
  
  device_port=$(get_device_port_by_index $index)
  cd $path
  # idf.py fullclean
  idf.py -p $device_port -b 115200 flash &
  cd -

  (( index++ ))
  if [ $index = $ESP_DEVICE_COUNT ];then
    break
  fi
done < <(tail -n +2 $csv_file_path)
cd $old_pwd

echo
echo
echo "Flashed :: $csv_file_path"
index=0
while IFS="," read -r path package_name
do
 
  path=$(eval echo "$path")
  # $ESP_IDF_HOME OR $VENDOR_HOME
  vend_path=$(echo "$path" | sed -e "s|ROOT|${VENDOR_HOME}|g")
  esp_path=$(echo $path | sed -e "s|ROOT|${ESP_IDF_HOME}|g")

  if [ -d "$vend_path" ]; then
    echo "$vend_path found."
    path=$vend_path
  elif [ -d "$esp_path" ]; then
    echo "$esp_path found."
    path=$esp_path
  fi
  device_port=$(get_device_port_by_index $index)
  echo "$device_port  ::  $package_name"
  (( index++ ))
  if [ $index = $ESP_DEVICE_COUNT ];then
    break
  fi
done < <(tail -n +2 $csv_file_path)

echo