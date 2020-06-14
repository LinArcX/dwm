#!/bin/sh
# Date is formatted like like this: "[Mon 01-01-00 00:00:00]"

dwm_jdate () {
    printf "%s" "$(jdate '+%Y/%m/%d %h')"
}
dwm_jdate

#printf "%s" "$(jdate +''%d'/'%m'/'%Y)"
#if [ "$IDENTIFIER" = "unicode" ]; then
#else
#    printf "DAT %s" "$(jdate +''%d'/'%m'/'%Y)"
#fi
#printf "📆 %s" "$(date "+%a %d-%m-%y %T")"
#printf "📆 %s" "$(jdate +%G'*'%d'*'%V'*'%Y)"
