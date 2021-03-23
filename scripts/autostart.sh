#!/bin/sh
display -backdrop -background '#3f3f3f' -window root /mnt/D/images/andrea-rodriguez.jpg
setxkbmap -model pc105 -layout us,ir -option grp:alt_shift_toggle &
./bar.sh &
