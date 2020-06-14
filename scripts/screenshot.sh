#!/bin/sh
export BRIGHTNESS=/sys/class/backlight/intel_backlight/brightness

DIR="${HOME}/Pictures"
DATE="$(date +%Y'-'%m'-'%d' '%H'-'%M'-'%S)"
NAME="${DIR}/Screenshot from ${DATE}.png"

# Check if the dir to store the screenshots exists, else create it:
if [ ! -d "${DIR}" ]; then
    mkdir -p "${DIR}";
    echo 100 |sudo tee $BRIGHTNESS; sleep 0.1; echo 4882 |sudo tee $BRIGHTNESS > /dev/null && 2>&1
fi

# Screenshot a selected window
if [ "$1" = "win" ]; then
    import -format png "${NAME}";
    echo 100 |sudo tee $BRIGHTNESS; sleep 0.1; echo 4882 |sudo tee $BRIGHTNESS > /dev/null && 2>&1
fi

# Screenshot the entire screen
if [ "$1" = "scr" ]; then
    import -format png -window root "${NAME}";
    notify-send --icon=gtk-info "Saved to: ${DIR}" "${NAME}"
    //xrefresh -solid white
    //echo 50 | sudo tee $BRIGHTNESS; sleep 0.1; echo 4000 | sudo tee $BRIGHTNESS
fi

# Screenshot a selected area
if [ "$1" = "area" ]; then
    import -format png "${NAME}";
    echo 100 |sudo tee $BRIGHTNESS; sleep 0.1; echo 4882 |sudo tee $BRIGHTNESS > /dev/null && 2>&1
fi
