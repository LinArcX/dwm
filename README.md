# dwm - dynamic window manager ![Language](https://img.shields.io/github/languages/top/LinArcX/dwm.svg?style=flat-square) ![RepoSize](https://img.shields.io/github/repo-size/LinArcX/dwm.svg?style=flat-square) ![Latest Tag](https://img.shields.io/github/tag/LinArcX/dwm.svg?colorB=green&style=flat-square)
dwm is an extremely fast, small, and dynamic window manager for X.

## Preview
!["gnulium"](./shots/empty_room.png "dwm")

## Requirements
In order to build this fork of dwm, you need:
- libX11-devel
- libXft-devel
- curl
- jcal
- rofi
- feh
- xsetroot
- numlockx
- setxkbmap
- alsa-utils
- font-iosevka
- xkblayout-state
- gnome-screenshot

Tip: if you want to use __pkexec__, you should first install `elogind` and start/enable it's service:

`sudo ln -s /etc/sv/elogind /var/service/`

After that install `xfce-polkit` and put this line into autostart.sh:

`/usr/libexec/xfce-polkit &`

## Patches
- [autostart](https://dwm.suckless.org/patches/autostart/)
- [gaps](https://dwm.suckless.org/patches/gaps/)
- [hide_vacant_tags](https://dwm.suckless.org/patches/hide_vacant_tags/)

### Status bar
I used this repo with some little changes:
https://github.com/joestandring/dwm-bar

## Configuration and Installation
Create a custom __config.h__ file and edit it to match your local setup (dwm is installed into the /usr/local namespace by default).
Afterwards enter the following command to build and install dwm (if necessary as root):

`make clean install`

## Running dwm
Add the following line to your .xinitrc to start dwm using __startx__:

`exec dwm`

In order to connect dwm to a specific display, make sure that the DISPLAY environment variable is set correctly, e.g.:

`DISPLAY=foo.bar:1 exec dwm`

(This will start dwm on display :1 of the host foo.bar.)

In order to display status info in the bar, you can do something
like this in your .xinitrc:

```
while xsetroot -name "`date` `uptime | sed 's/.*,//'`"
do
	sleep 1
done &
exec dwm
```

## Configuration
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.

## Contributing
![Open PR](https://img.shields.io/github/issues-pr-raw/LinArcX/dwm.svg?style=flat-square) ![Closed PR](https://img.shields.io/github/issues-pr-closed/LinArcX/dwm.svg?style=flat-square)
1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Bugs
![Open Issues](https://img.shields.io/github/issues-raw/LinArcX/dwm.svg?style=flat-square) ![Issues](https://img.shields.io/github/issues-closed-raw/LinArcX/dwm.svg?style=flat-square)

Bugs should be reported [here](https://github.com/LinArcX/dwm/issues) on the Github issues page.

## TODO
- [ ] Alsa not wokring
- [x] Change default layout to monocle

## Credits
E-Mail:linarcx@gmail.com

<h1 align="center">
	<img width="200" src="./assets/dwm.svg" alt="dwm">
	<br>
</h1>

## License
![License](https://img.shields.io/github/license/LinArcX/Gnulium.svg?style=flat-square)
