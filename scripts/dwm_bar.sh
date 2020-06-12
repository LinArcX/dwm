#!/bin/sh
# Dependencies: xorg-xsetroot

# Import functions with "$include /route/to/module"
# It is recommended that you place functions in the subdirectory ./bar-functions and use: . "$DIR/bar-functions/dwm_example.sh"

# Store the directory the script is running from
LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

# Change the appearance of the module identifier.
# If this is set to "unicode", then symbols will be used as identifiers instead of text. E.g. [📪 0] instead of [MAIL 0].
# Requires a font with adequate unicode character support
export IDENTIFIER="unicode"

# Change the charachter(s) used to seperate modules. If two are used, they will be placed at the start and end.
export SEP="|"
. "$DIR/bar-functions/dwm_jdate.sh"
. "$DIR/bar-functions/dwm_date.sh"
. "$DIR/bar-functions/dwm_time.sh"
. "$DIR/bar-functions/dwm_alsa.sh"
. "$DIR/bar-functions/dwm_keyboard.sh"

# Update dwm status bar every second
while true
do
    xsetroot -name "$(dwm_jdate)$(dwm_date)$(dwm_time)$(dwm_alsa)$(dwm_keyboard)"
    sleep 1s
done

#export SEP1="["
#export SEP2="]"
# Import the modules
#. "$DIR/bar-functions/dwm_resources.sh"
#. "$DIR/bar-functions/dwm_weather.sh"
#. "$DIR/bar-functions/dwm_cmus.sh"
#. "$DIR/bar-functions/dwm_network.sh"
#. "$DIR/bar-functions/dwm_vpn.sh"
#. "$DIR/bar-functions/dwm_battery.sh"
#. "$DIR/bar-functions/dwm_backlight.sh"
