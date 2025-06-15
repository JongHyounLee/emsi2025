#!/bin/bash

MODULES=(
    buzzerdrv.ko
    fnddrv.ko
    leddrv.ko
    textlcddrv.ko
)

for modules in "${drivers[@]}"
do
    echo "loading: $modules"
    sudo insmod "$modules"
    if [ $? -eq 0 ]; then
        echo "SUCCESS: $modules ins complete"
    else
        echo "ERROR: $modules ins Failed"
        exit 1 
    fi
done

echo "insmod all complete"