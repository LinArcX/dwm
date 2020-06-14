#!/bin/sh

du () {
    HOMEFREE=$(df -h | grep '/dev/sda3' | awk '{print $4}')
    DFREE=$(df -h | grep '/dev/sda5' | awk '{print $4}')
    EFREE=$(df -h | grep '/dev/sda6' | awk '{print $4}')
    printf "Home:%s D:%s E:%s" "$HOMEFREE" "$DFREE" "$EFREE"
}
du
