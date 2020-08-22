#!/bin/sh
numlockx on &
display -backdrop -background '#3f3f3f' -window root /home/linarcx/Pictures/sierra.jpg
setxkbmap -model pc105 -layout us,ir -option grp:alt_shift_toggle &

./bar.sh &

st &
firefox &
dunst &

while sleep 600; do
    pgrep zathura
    if [ $? -eq 0 ]; then
        slock;
    fi;
done &

#/usr/libexec/policykit-1-pantheon/io.elementary.desktop.agent-polkit &
#watch -n 20 '/usr/local/bin/slock' &>/dev/null &
#> /dev/null 2>&1
