#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=12" };
static const char dmenufont[]       = "monospace:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                              instance      title       tags mask     isfloating   monitor */
    { "",                                 "Emulator",   NULL,       0,            1,           -1 },
    { "",                                 "Xephyr",     NULL,       0,            1,           -1 },
    { "Alacritty",                        "",           NULL,       0,            0,           -1 },
    { "mpv",                              "",           NULL,       0,            1,           -1 },
    { "Xephyr",                           "",           NULL,       0,            1,           -1 },
    { "Emulator",                         "",           NULL,       0,            1,           -1 },
    { "qutebrowser",                      "",           NULL,       2,            0,           -1 },
    { "Brave-browser",                    "",           NULL,       2,            0,           -1 },
    { "Zathura",                          "",           NULL,       4,            0,           -1 },
    { "Anki",                             "",           NULL,       4,            0,           -1 },
    { "Fritzing",                         "",           NULL,       4,            0,           -1 },
    { "musescore",                        "",           NULL,       4,            0,           -1 },
    { "MuseScore3",                       "",           NULL,       4,            0,           -1 },
    { "qBittorrent",                      "",           NULL,       4,            0,           -1 },
    { "qbittorrent",                      "",           NULL,       4,            0,           -1 },
    { "sun-awt-X11-XFramePeer",           "",           NULL,       4,            0,           -1 },
    { "de-neemann-digital-gui-Main",      "",           NULL,       4,            0,           -1 },
    { "CPUEmulatorMain",                  "",           NULL,       4,            0,           -1 },
    { "HardwareSimulatorMain",            "",           NULL,       4,            0,           -1 },
    { "HackAssemblerMain",                "",           NULL,       4,            0,           -1 },
    { "VMEmulatorMain",                   "",           NULL,       4,            0,           -1 },
    { "Fritzing-bin",                     "",           NULL,       4,            0,           -1 },
    { "com-cburch-logisim-Main",          "",           NULL,       4,            0,           -1 },
    { "Tor Browser",                      "",           NULL,       8,            0,           -1 },

    //{ "Emacs",                            "",           NULL,       4,            0,           -1 },
    //{ "Evince",                           "",           NULL,       4,            0,           -1 },
    //{ "Foliate",                          "",           NULL,       4,            0,           -1 },
    //{ "transmission-gtk",                 "",           NULL,       4,            0,           -1 },
    //{ "Logseq",                           "",           NULL,       4,            1,           -1 },
    //{ "Eclipse",                          "",           NULL,       8,            0,           -1 },
    //{ "nyxt",                             "",           NULL,       8,            0,           -1 },
    //{ "com.github.johnfactotum.Foliate",  "",           NULL,       8,            0,           -1 },
    //{ "Microsoft Teams - Preview",        "",           NULL,       4,            0,           -1 },
    //{ "st-256color",                      "",           NULL,       0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",     monocle },
	{ "[]=",     tile },    /* first entry is default */
  { "##",      gaplessgrid },
  { "||",      bstack },
  { "==",      bstackhoriz },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }
#define PrintScreenDWM    0x0000ff61

#define  SCRIPTS_PATH       "$HOME/VoidConf/home/.local/bin/scripts/03_x/"
#define  SCREENSHOT_FULL    SCRIPTS_PATH "screenshot_fullscreen.sh"
#define  SCREENSHOT_REGION  SCRIPTS_PATH "screenshot_region.sh"
#define  ALSATOGGLE         SCRIPTS_PATH "alsa_toggle.sh"
#define  ALSA_DECREASE      SCRIPTS_PATH "alsa_decrease.sh"
#define  ALSA_INCREASE      SCRIPTS_PATH "alsa_increase.sh"

#define  MENU_PATH          "$HOME/VoidConf/home/.local/bin/menu/"
#define  PROJECTS           MENU_PATH "projects.sh"
#define  GUIAPPS            MENU_PATH "gui_apps.sh"
#define  BOOKS              MENU_PATH "books.sh"
#define  MOUNT_DEVICES      MENU_PATH "mount_devices.sh"
#define  UNMOUNT_DEVICES    MENU_PATH "unmount_devices.sh"
#define  POWERMANAGER       MENU_PATH "power_manager.sh"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *mutecmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "sset", "PCM", "5-", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "sset", "PCM", "5+", "unmute", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY,            XK_r,                    spawn,     SHCMD("alacritty -e open_lf_at_home.sh")},
  { MODKEY,            XK_Return,               spawn,     SHCMD("cd $(xcwd); exec alacritty")},

  { MODKEY|ShiftMask,  XK_p,                    spawn,     SHCMD(PROJECTS)},
  { MODKEY|ShiftMask,  XK_g,                    spawn,     SHCMD(GUIAPPS)},
  { MODKEY|ShiftMask,  XK_b,                    spawn,     SHCMD(BOOKS)},
  { MODKEY|ShiftMask,  XK_m,                    spawn,     SHCMD(MOUNT_DEVICES)},
  { MODKEY|ShiftMask,  XK_u,                    spawn,     SHCMD(UNMOUNT_DEVICES)},
  { MODKEY|ShiftMask,  XK_e,                    spawn,     SHCMD(POWERMANAGER)},

  { 0,                 XF86XK_AudioMute,        spawn,     SHCMD(ALSATOGGLE)},
  { 0,                 XF86XK_AudioRaiseVolume, spawn,     SHCMD(ALSA_INCREASE)},
  { 0,                 XF86XK_AudioLowerVolume, spawn,     SHCMD(ALSA_DECREASE)},
	{ 0,                 XF86XK_AudioNext,        spawn,     SHCMD("mpc next") },
	{ 0,                 XF86XK_AudioPrev,        spawn,     SHCMD("mpc prev") },
	{ 0,                 XF86XK_AudioPause,       spawn,     SHCMD("mpc toggle") },
	{ 0,                 XF86XK_AudioPlay,        spawn,     SHCMD("mpc toggle") },

  { 0,                 PrintScreenDWM,          spawn,     SHCMD(SCREENSHOT_FULL)},
  { MODKEY,            PrintScreenDWM,          spawn,     SHCMD(SCREENSHOT_REGION)},

  { MODKEY,            XK_b,                    togglebar,      {0} },
  { MODKEY,            XK_j,                    focusstack,     {.i = +1 } },
  { MODKEY,            XK_k,                    focusstack,     {.i = -1 } },
  { MODKEY,            XK_i,                    incnmaster,     {.i = +1 } },
  { MODKEY,            XK_d,                    incnmaster,     {.i = -1 } },
  { MODKEY,            XK_h,                    setmfact,       {.f = -0.05} },
  { MODKEY,            XK_l,                    setmfact,       {.f = +0.05} },
  { MODKEY,            XK_Return,               zoom,           {0} },
  { MODKEY,            XK_Tab,                  view,           {0} },
  { MODKEY|ShiftMask,  XK_q,                    killclient,     {0} },

  { MODKEY,            XK_t,                    setlayout,      {.v = &layouts[0]} },
  { MODKEY,            XK_m,                    setlayout,      {.v = &layouts[1]} },
  { MODKEY,            XK_g,                    setlayout,      {.v = &layouts[2]} },
  { MODKEY,            XK_u,                    setlayout,      {.v = &layouts[3]} },
	{ MODKEY,            XK_o,                    setlayout,      {.v = &layouts[4]} },
  { MODKEY,            XK_f,                    setlayout,      {.v = &layouts[5]} },
  { MODKEY,            XK_space,                setlayout,      {0} },
  { MODKEY|ShiftMask,  XK_space,                togglefloating, {0} },

  { MODKEY,            XK_0,                    view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,  XK_0,                    tag,            {.ui = ~0 } },
  { MODKEY,            XK_comma,                focusmon,       {.i = -1 } },
  { MODKEY,            XK_period,               focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,  XK_comma,                tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,  XK_period,               tagmon,         {.i = +1 } },

  TAGKEYS(             XK_1,                      0)
  TAGKEYS(             XK_2,                      1)
  TAGKEYS(             XK_3,                      2)
  TAGKEYS(             XK_4,                      3)
  TAGKEYS(             XK_5,                      4)
  TAGKEYS(             XK_6,                      5)
  TAGKEYS(             XK_7,                      6)
  TAGKEYS(             XK_8,                      7)
  TAGKEYS(             XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,       0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,       0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,       0,              Button2,        zoom,           {0} },
  { ClkStatusText,     0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,      MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,      MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,      MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,         0,              Button1,        view,           {0} },
  { ClkTagBar,         0,              Button3,        toggleview,     {0} },
  { ClkTagBar,         MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,         MODKEY,         Button3,        toggletag,      {0} },
};
