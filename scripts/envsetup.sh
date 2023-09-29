#!/bin/bash

SOURCE=${BASH_SOURCE[0]}
while [ -L "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
  SOURCE=$(readlink "$SOURCE")
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done

export VENDOR_HOME=$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )
export VENDOR_PACKAGE="$VENDOR_HOME"/packages
export EROOT="$(dirname "$VENDOR_HOME")"
export ESP_IDF_HOME="$EROOT"/esp-idf
export IDF_EXAMPLE_PACKAGE="$ESP_IDF_HOME"/examples
export IDF_BUILD_TARGET="esp32"
export DEVICE_PORT="/dev/ttyACM0"

function set_alias()
{
  alias "$1"="${@:2}"
  echo -e "$(alias $1)"
}

GIT_URL="https://github.com/espressif/esp-idf.git"
VERIFIED_BRANCH="2ac972e2c7a46c95d681a9b044d0683fdcafe66e"

[[ ! -d $ESP_IDF_HOME ]] && 
cd $EROOT && 
git clone $GIT_URL &&
cd $ESP_IDF_HOME &&
git checkout -b $VERIFIED_BRANCH &&
cd $EROOT &&
bash $ESP_IDF_HOME/install.sh

echo "Running $ESP_IDF_HOME/export.sh ..."
source $ESP_IDF_HOME/export.sh

echo -e "EROOT\t\t:\t$EROOT"
echo -e "ESP_IDF_HOME\t:\t$ESP_IDF_HOME"
echo -e "VENDOR_HOME\t:\t$VENDOR_HOME"
echo -e "VENDOR_PACKAGE\t:\t$VENDOR_PACKAGE"
echo
set_alias eroot "cd $EROOT"
set_alias build.sh "source $VENDOR_HOME/build.sh"
set_alias build_all.sh "source $VENDOR_HOME/build_all.sh"
set_alias flash.sh "source $VENDOR_HOME/flash.sh"
set_alias push.sh "source $VENDOR_HOME/push.sh"
