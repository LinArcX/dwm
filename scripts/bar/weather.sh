#!/bin/sh
# Dependencies: curl

# Change the value of LOCATION to match your city
weather() {
    LOCATION=tehran
    if [ "$IDENTIFIER" = "unicode" ]; then
        #printf "%s" "$(curl -s wttr.in/$LOCATION?format=1)"
        printf "%s" "$(curl wttr.in/Tehran?format=3)"
    else
        printf "WEA %s" "$(curl -s wttr.in/$LOCATION?format=1 | grep -o "[0-9].*")"
    fi
}
weather
