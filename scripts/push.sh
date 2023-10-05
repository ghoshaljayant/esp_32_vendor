#!/bin/bash

old_pwd=$(pwd)
echo "$old_pwd"

result="FAIL"

RUN_VERIFICATION()
{
    result="PASS"
}

RUN_VERIFICATION

if [ "$result" = "PASS" ];then

    cd "$VENDOR_HOME" &&
    git add -A &&
    git commit -m "New changes" &&
    git push

else

    echo "push failed"

fi

cd $old_pwd
