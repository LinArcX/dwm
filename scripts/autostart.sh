#!/bin/sh
numlockx on &
feh --bg-fill /home/linarcx/Pictures/sierra.jpg &
setxkbmap -model pc105 -layout us,ir -option grp:alt_shift_toggle &

./bar.sh &

st &
firefox &
dunst &
while sleep 600; do slock; done &

#/usr/libexec/policykit-1-pantheon/io.elementary.desktop.agent-polkit &
#watch -n 20 '/usr/local/bin/slock' &>/dev/null &
#watch -n 20 /usr/local/bin/slock &
#> /dev/null 2>&1
