#!/bin/sh
# Date is formatted like like this: "[Mon 01-01-00 00:00:00]"

dwm_date () {
    printf "%s" "$(date '+%Y/%m/%d %a')"
}
dwm_date

#if [ "$IDENTIFIER" = "unicode" ]; then
#else
#    printf "DAT %s" "$(date '+%d/%m/%Y')"
#fi
#printf "📆 %s" "$(date "+%a %d-%m-%y %T")"
