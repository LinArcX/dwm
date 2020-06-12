#!/bin/sh
# Dependencies: xorg-setxkbmap

dwm_keyboard () {
    if [ "$IDENTIFIER" = "unicode" ]; then
        #layout=$(xkblayout-state print %s)
        printf "⌨ %s" "$(xkblayout-state print %s)"
        #printf "⌨ %s" "$(setxkbmap -query | awk '/layout/{print $2}')"
    else
        printf "KEY %s" "$(xkblayout-state print %s)"
    fi
    printf "%s\n" "$SEP"
}

dwm_keyboard
