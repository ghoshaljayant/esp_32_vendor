#! /bin/bash

if [ "$1" = "-h" ];then
  echo "source csv_parser.sh csv_file_path"
  return 0
fi

while IFS="," read -r path package_name
do
  echo "$path"
  echo "$package_name"
  echo ""
  flash.sh "$path" "$package_name"
done < <(tail -n +2 $1)
