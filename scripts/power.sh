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

# source configuration or use default values
#if [ -f $HOME/.config/rofi-power/config ]; then
#  source $HOME/.config/rofi-power/config
#else
# LAUNCHER="rofi -dmenu -width 40 -theme gruvbox-dark-soft"
#fi

# Show exit wm option if exit command is provided as an argument
#if [ ${#1} -gt 0 ]; then
#  OPTIONS="Exit window manager\n$OPTIONS"
#fi
