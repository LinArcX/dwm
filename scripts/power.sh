#!/bin/sh

OPTIONS="Exit\nZzz\nReboot\nPower-off"
LAUNCHER="rofi -dmenu -width 40 -theme gruvbox-dark-soft"
option=`echo $OPTIONS | $LAUNCHER | awk '{print $1}' | tr -d '\r\n'`

if [ ${#option} -gt 0 ]
then
    case $option in
      Exit)
        pkill -u $USER
        ;;
      Zzz)
        sudo zzz
        ;;
      Reboot)
        sudo reboot
        ;;
      Power-off)
        sudo shutdown -h now
        ;;
      *)
        ;;
    esac
fi
