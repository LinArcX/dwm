#!/bin/sh
# Dependencies: xorg-xsetroot

# Store the directory the script is running from
LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

# Change the appearance of the module identifier.
# If this is set to "unicode", then symbols will be used as identifiers instead of text. E.g. [📪 0] instead of [MAIL 0].
# Requires a font with adequate unicode character support
export IDENTIFIER="unicode"

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
    #xsetroot -name "$(cpu_ram)|$(du)|$(jdate)|$(date)|$(time)|$(alsa)|$(keyboard)"
    xsetroot -name " $(cpu_ram) | $(du) | $(dwm_jdate) | $(dwm_date) | $(time) | $(alsa) | $(keyboard)"
    sleep 1s
done

# Import functions with "$include /route/to/module"
# It is recommended that you place functions in the subdirectory ./bar-functions and use: . "$DIR/bar-functions/dwm_example.sh"

# Change the charachter(s) used to seperate modules. If two are used, they will be placed at the start and end.
#export SEP="|"
#export SEP1="["
#export SEP2="]"

# Import the modules
#. "$DIR/bar-functions/dwm_weather.sh"
#. "$DIR/bar-functions/dwm_cmus.sh"
#. "$DIR/bar-functions/dwm_network.sh"
#. "$DIR/bar-functions/dwm_vpn.sh"
#. "$DIR/bar-functions/dwm_battery.sh"
#. "$DIR/bar-functions/dwm_backlight.sh"
