#!/bin/sh
# Dependencies: xorg-setxkbmap

keyboard () {
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "%s" "$(xkblayout-state print %s | awk '{print toupper($0)}')"
    else
        printf "KEY %s" "$(xkblayout-state print %s)"
    fi
}
keyboard
