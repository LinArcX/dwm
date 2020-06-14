#!/bin/sh
numlockx on &
feh --bg-fill ../assets/sierra.jpg &
setxkbmap -model pc105 -layout us,ir -option grp:alt_shift_toggle &

./bar.sh &
/usr/libexec/policykit-1-pantheon/io.elementary.desktop.agent-polkit &

st &
firefox &
