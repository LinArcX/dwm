#!/bin/sh

# A dwm_bar function that shows the current date and time
# Joe Standring <git@joestandring.com>
# GNU GPLv3

# Date is formatted like like this: "[Mon 01-01-00 00:00:00]"
dwm_time () {
    #printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then

        #date '+%H:%M:%S'
        #printf "📆 %s" "$(date "+%a %d-%m-%y %T")"
        printf " %s " "$(date '+%H:%M:%S')"
    else
        printf "%s" "$(date '+%H:%M:%S')"
    fi
    printf "%s\n" "$SEP"
}

dwm_time
