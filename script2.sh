#!/bin/bash
# My first script

if [ $# -eq 0 ]; then
    echo "Please provide file path"
    exit 1
fi

echo Source files:
ls $1 | grep *.c

echo Header files:
ls $1 | grep *.h

echo Script files:
ls $1 | grep *.sh

echo Text files:
ls $1 | grep *.txt

for file in $1/*
do
    if [[ $file == *"."* ]]; then
        if  [[ $file != *".c"* ]] && [[ $file != *".h"* ]] &&[[ $file != *".sh"* ]] && [[ $file != *".txt"* ]];then
            echo $(basename $file)
        fi
    fi
done