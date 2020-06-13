#!/bin/sh
# Dependencies: xorg-setxkbmap

dwm_keyboard () {
    if [ "$IDENTIFIER" = "unicode" ]; then
        printf "⌨ %s" "$(xkblayout-state print %s)"
    else
        printf "KEY %s" "$(xkblayout-state print %s)"
    fi
    printf "%s\n" "$SEP"
}

dwm_keyboard

#layout=$(xkblayout-state print %s)
#printf "⌨ %s" "$(setxkbmap -query | awk '/layout/{print $2}')"
