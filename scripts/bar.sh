#!/bin/sh
# Dependencies: xorg-xsetroot

# Store the directory the script is running from
LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

# Change the appearance of the module identifier.
# If this is set to "unicode", then symbols will be used as identifiers instead of text. E.g. [📪 0] instead of [MAIL 0].
# Requires a font with adequate unicode character support
export IDENTIFIER="unicode"

#. "$DIR/bar-functions/dwm_network.sh"
#. "$DIR/bar-functions/dwm_vpn.sh"
. "$DIR/bar/weather.sh"
. "$DIR/bar/cpu_ram.sh"
. "$DIR/bar/du.sh"
. "$DIR/bar/dwm_jdate.sh"
. "$DIR/bar/date.sh"
. "$DIR/bar/time.sh"
. "$DIR/bar/alsa.sh"
. "$DIR/bar/keyboard.sh"

# Update dwm status bar every second
while true
do
    xsetroot -name " $(weather) | $(cpu_ram) | $(du) | $(dwm_jdate) | $(dwm_date) | $(time) | $(alsa) | $(keyboard)"
    sleep 1s
done
