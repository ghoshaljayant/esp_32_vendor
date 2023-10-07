#!/bin/bash

result="FAIL"

function detect_device()
{
    export ESP_DEVICES="NULL"
    device_port_list=$(ls /dev |grep -E 'ttyACM|ttyUSB')

    device_index=0
    if [ "$device_port_list" != "" ];then
        while IFS= read -r device_port ; do        
            eval "export DEVICE_PORT_$device_index=/dev/$device_port"
            (( device_index++ ))  
        done <<< "$device_port_list"
    fi

    case $device_index in
    0)  export ESP_DEVICE_STATUS="NULL"
        ;;
    1)  export ESP_DEVICE_STATUS="SINGLE_DEVICE_CONNECTED"
        ;;
    *)  export ESP_DEVICE_STATUS="MULTI_DEVICE_CONNECTED"
        ;;
    esac

    export ESP_DEVICE_COUNT="$device_index"
}

function list_device_port_by_index()
{
    device_port_list=$(ls /dev |grep -E 'ttyACM|ttyUSB')

    device_index=0
    if [ "$device_port_list" != "" ];then
        while IFS= read -r device_port ; do        
            echo "$device_index. $device_port"
            (( device_index++ ))  
        done <<< "$device_port_list"
    fi
}

function get_device_port_by_index()
{
    device_port_list=$(ls /dev |grep -E 'ttyACM|ttyUSB')
    requested_index=$1
    device_index=0
    if [ "$device_port_list" != "" ];then
        while IFS= read -r device_port ; do
            if [ "$device_index" = "$requested_index" ];then
                echo "/dev/$device_port"
            fi            
            (( device_index++ ))  
        done <<< "$device_port_list"
    fi
}

function lunch()
{
    target_array=()
    target_string=$(ls $VENDOR_HOME/targets|grep -e ".csv"|cut -d "." -f 1)

    IFS=$'\n' read -r -d '' -a target_array <<< "$target_string"

    for key in "${!target_array[@]}"
    do
        echo "$key.) ${target_array[$key]}"
    done

    read selection
    export ESP_TARGET="${target_array[$selection]}"
    echo
    echo "$ESP_TARGET"
    echo
}
