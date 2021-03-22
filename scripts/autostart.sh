#!/bin/sh
numlockx on &
display -backdrop -background '#3f3f3f' -window root /home/linarcx/Pictures/sierra.jpg
setxkbmap -model pc105 -layout us,ir -option grp:alt_shift_toggle &

./bar.sh &

st &
firefox &
dunst &
emacs --daemon
emacsclient -s /var/run/user/1000/emacs/server -c -n -a emacs &

while sleep 600; do
    pgrep zathura
    if [ $? -eq 0 ]; then
        slock;
    fi;
done &
