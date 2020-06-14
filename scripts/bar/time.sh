#!/bin/sh
# Date is formatted like like this: "[Mon 01-01-00 00:00:00]"

time () {
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "%s" "$(date '+%H:%M:%S')"
    else
        printf "%s" "$(date '+%H:%M:%S')"
    fi
}
time

#printf "📆 %s" "$(date "+%a %d-%m-%y %T")"
