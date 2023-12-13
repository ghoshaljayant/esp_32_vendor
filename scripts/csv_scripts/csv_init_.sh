#! /bin/bash


function csv_init()
{
  SOURCE=${BASH_SOURCE[0]}
  while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
    SOURCE=$(readlink "$SOURCE")
    [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
  done
  export MY_PATH=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )

  csv_file_path="$VENDOR_HOME/targets/$ESP_TARGET.csv"

  if [ ! -f "$csv_file_path" ];then
    echo "Invalid target name: $ESP_TARGET"
    return -1
  fi

  echo "Valid target name: $ESP_TARGET"

  # check if any device is connected or not
  source $MY_PATH/tools.sh
  detect_device
  if [ "$ESP_DEVICE_COUNT" = "0" ];then
    echo "No device connected !!"
    return -1
  fi
}