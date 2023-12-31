#!/bin/bash

old_pwd=$(pwd)
echo "$old_pwd"
SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done

MY_PATH=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
export VENDOR_HOME="$( dirname $MY_PATH )"
export VENDOR_PACKAGE="$VENDOR_HOME"/packages
export VENDOR_COMPONENTS="$VENDOR_HOME"/components
export EROOT="$(dirname "$VENDOR_HOME")"
export ESP_IDF_HOME="$EROOT"/esp-idf
export IDF_EXAMPLE_PACKAGE="$ESP_IDF_HOME"/examples
export IDF_BUILD_TARGET="esp32"
export DEVICE_PORT="/dev/ttyACM0"
export STANDALONE_SCRIPT_PATH="$VENDOR_HOME"/scripts/standalone
export CSV_SCRIPT_PATH="$VENDOR_HOME"/scripts/csv_scripts


function set_alias()
{
  alias "$1"="${@:2}"
  echo -e "$(alias $1)"
}

GIT_URL="https://github.com/espressif/esp-idf.git"
#VERIFIED_BRANCH="2ac972e2c7a46c95d681a9b044d0683fdcafe66e"
VERIFIED_BRANCH="1726ce888dfe08a7c94c9e213876fb91d40a7d57"
RELEASE_BRANCH="v5.1.1"


[[ ! -d $ESP_IDF_HOME ]] && 
cd $EROOT && 
git clone -b $RELEASE_BRANCH --recursive $GIT_URL &&
cd $ESP_IDF_HOME &&
cd $EROOT &&
bash $ESP_IDF_HOME/install.sh

echo "Running $ESP_IDF_HOME/export.sh ..."
source $ESP_IDF_HOME/export.sh
source $STANDALONE_SCRIPT_PATH/tools.sh

echo -e "List all the environmental variables :"
echo -e "--------------------------------------"
echo -e "EROOT\t\t:\t$EROOT"
echo -e "ESP_IDF_HOME\t:\t$ESP_IDF_HOME"
echo -e "VENDOR_HOME\t:\t$VENDOR_HOME"
echo -e "VENDOR_PACKAGE\t:\t$VENDOR_PACKAGE"
echo -e "VENDOR_COMPONENTS\t:\t$VENDOR_COMPONENTS"
echo
echo -e "List all the aliases :"
echo -e "----------------------"



[[ ! -d $STANDALONE_SCRIPT_PATH ]] && 

[[ ! -d $CSV_SCRIPT_PATH ]] && 

set_alias esp "cd $EROOT"
set_alias build.sh "source $STANDALONE_SCRIPT_PATH/build.sh"
set_alias build_all.sh "source $STANDALONE_SCRIPT_PATH/build_all.sh"
set_alias flash.sh "source $STANDALONE_SCRIPT_PATH/flash.sh"
set_alias push.sh "source $STANDALONE_SCRIPT_PATH/push.sh"
set_alias monitor_targets "source $CSV_SCRIPT_PATH/csv_monitor.sh"
set_alias flash_targets "source $CSV_SCRIPT_PATH/csv_flasher.sh"
set_alias parse_targets "source $CSV_SCRIPT_PATH/csv_parser.sh"
set_alias targets "cd $VENDOR_HOME/targets/"
set_alias list_targets "lunch"


cd $old_pwd
