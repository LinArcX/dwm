#!/bin/sh

cpu_ram () {
    # Used and total memory
    MEMUSED=$(free -h | awk '(NR == 2) {print $3}')
    MEMTOT=$(free -h |awk '(NR == 2) {print $2}')

    # CPU temperature
    CPU=$(cat /sys/class/thermal/thermal_zone*/temp | rev | cut -c 4- | rev | sed -n 2p)

    if [ "$IDENTIFIER" = "unicode" ]; then
        printf " %s/%s  %s" "$MEMUSED" "$MEMTOT" "$CPU"
    else
        printf "MEM %s/%s CPU %s" "$MEMUSED" "$MEMTOT" "$CPU"
    fi
}
cpu_ram
