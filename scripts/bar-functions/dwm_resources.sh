#!/bin/sh

# A dwm_bar function to display information regarding system memory, CPU temperature, and storage
# Joe Standring <git@joestandring.com>
# GNU GPLv3

dwm_resources () {
    # Used and total memory
    MEMUSED=$(free -h | awk '(NR == 2) {print $3}')
    MEMTOT=$(free -h |awk '(NR == 2) {print $2}')

    # CPU temperature
    CPU=$(cat /sys/class/thermal/thermal_zone*/temp | rev | cut -c 4- | rev | sed -n 2p)

    # Used and total storage in /home (rounded to 1024B)
    VOIDFREE=$(df -h | grep '/dev/sda3' | awk '{print $4}')
    DFREE=$(df -h | grep '/dev/sda5' | awk '{print $4}')
    EFREE=$(df -h | grep '/dev/sda6' | awk '{print $4}')

    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "MEM %s/%s CPU %s Void: %s E: %s D: %s" "$MEMUSED" "$MEMTOT" "$CPU" "$VOIDFREE" "$DFREE" "$EFREE"
    else
        printf "MEM %s/%s CPU %s Void %s E: %s D: %s" "$MEMUSED" "$MEMTOT" "$CPU" "$VOIDFREE" "$DFREE" "$EFREE"
    fi
    printf "%s\n" "$SEP"
}

dwm_resources

#printf "%s" "$SEP1"
#CPU=$(sysctl -n hw.sensors.cpu0.temp0 | cut -d. -f1)
#STOUSED=$(df -h | grep '/home$' | awk '{print $3}')
#STOPER=$(df -h | grep '/home$' | awk '{print $5}')
#STOTOT=$(df -h | grep '/home$' | awk '{print $2}')
