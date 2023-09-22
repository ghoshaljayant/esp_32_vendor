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

export IDF_BUILD_TARGET="esp32"


alias eroot="cd $EROOT"
alias build.sh="source $VENDOR_HOME/build.sh"
alias build_all.sh="source $VENDOR_HOME/build_all.sh"

[[ ! -d $ESP_IDF_HOME ]] && cd $EROOT && git clone https://github.com/espressif/esp-idf.git && bash $ESP_IDF_HOME/install.sh

echo "Running $ESP_IDF_HOME/export.sh ..."
source $ESP_IDF_HOME/export.sh

echo -e "EROOT\t\t:\t$EROOT"
echo -e "ESP_IDF_HOME\t:\t$ESP_IDF_HOME"
echo -e "VENDOR_HOME\t:\t$VENDOR_HOME"
echo -e "VENDOR_PACKAGE\t:\t$VENDOR_PACKAGE"