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
    { "nyxt",                             "",           NULL,       4,            0,           -1 },
    { "Tor Browser",                      "",           NULL,       4,            0,           -1 },
    { "Anki",                             "",           NULL,       4,            0,           -1 },
    { "Zathura",                          "",           NULL,       4,            0,           -1 },
    { "Evince",                           "",           NULL,       4,            0,           -1 },
    { "Foliate",                          "",           NULL,       4,            0,           -1 },
    { "Eclipse",                          "",           NULL,       4,            0,           -1 },
    { "com.github.johnfactotum.Foliate",  "",           NULL,       4,            0,           -1 },
    //{ "Emacs",                            "",           NULL,       4,            0,           -1 },
    //{ "microsoft teams - preview",        "",           NULL,       4,            0,           -1 },
    //{ "Microsoft Teams - Preview",        "",           NULL,       4,            0,           -1 },
    //{ "Brave-browser",                    "",           NULL,       5,            0,           -1 },
    //{ "st-256color",                      "",           NULL,       0,            0,           -1 },
    //{ "transmission-gtk",                 "",           NULL,       4,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
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

//#define  MENU_PATH          "$HOME/VoidConf/home/.local/bin/menu/"
//#define  PACKAGES           MENU_PATH "01_packages.sh"
//#define  PLACES             MENU_PATH "02_places.sh"
//#define  XBPS               MENU_PATH "03_xbps.sh"
//#define  DEVICES            MENU_PATH "04_devices.sh"
//#define  NETWORK            MENU_PATH "05_network.sh"
//#define  SCRIPTS            MENU_PATH "06_scripts.sh"
//#define  SERVICES           MENU_PATH "07_services.sh"
//#define  CHANNELS           MENU_PATH "08_channels.sh"
//#define  MOUNT_DEVICES      MENU_PATH "09_mount_devices.sh"
//#define  UNMOUNT_DEVICES    MENU_PATH "10_unmount_devices.sh"
//#define  OTHERS             MENU_PATH "11_others.sh"
//#define  BOOKS              MENU_PATH "12_books.sh"
//#define  POWERMANAGER       MENU_PATH "99_power_manager.sh"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
//static const char *dmenucmd[] = { "sh", "-c", POWERMANAGER };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *mutecmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "sset", "PCM", "5-", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "sset", "PCM", "5+", "unmute", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  //{ MODKEY|ShiftMask,  XK_e,                    spawn,     SHCMD(POWERMANAGER)},
  { MODKEY,            XK_r,                    spawn,     SHCMD("alacritty -e open_lf_at_home.sh")},
  { MODKEY,            XK_Return,               spawn,     {.v = termcmd }},
  //{ MODKEY,            XK_F1,                   spawn,     SHCMD(PACKAGES)},
  //{ MODKEY,            XK_F2,                   spawn,     SHCMD(PLACES)},
  //{ MODKEY,            XK_F3,                   spawn,     SHCMD(XBPS)},
  //{ MODKEY,            XK_F4,                   spawn,     SHCMD(DEVICES)},
  //{ MODKEY,            XK_F5,                   spawn,     SHCMD(NETWORK)},
  //{ MODKEY,            XK_F6,                   spawn,     SHCMD(SCRIPTS)},
  //{ MODKEY,            XK_F7,                   spawn,     SHCMD(SERVICES)},
  //{ MODKEY,            XK_F8,                   spawn,     SHCMD(CHANNELS)},
  //{ MODKEY,            XK_F9,                   spawn,     SHCMD(MOUNT_DEVICES)},
  //{ MODKEY,            XK_F10,                  spawn,     SHCMD(UNMOUNT_DEVICES)},
  //{ MODKEY,            XK_F11,                  spawn,     SHCMD(OTHERS)},
  //{ MODKEY,            XK_F12,                  spawn,     SHCMD(BOOKS)},
  { 0,                 XF86XK_AudioMute,        spawn,     SHCMD(ALSATOGGLE)},
  //{ 0,                 XF86XK_AudioMute,        spawn,     SHCMD("amixer set Master toggle")},
  { 0,                 XF86XK_AudioRaiseVolume, spawn,     SHCMD(ALSA_INCREASE)},
  //{ 0,                 XF86XK_AudioRaiseVolume, spawn,     SHCMD("amixer set Master 5%+")},
  { 0,                 XF86XK_AudioLowerVolume, spawn,     SHCMD(ALSA_DECREASE)},
  //{ 0,                 XF86XK_AudioLowerVolume, spawn,     SHCMD("amixer set Master 5%-")},
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
  { MODKEY,            XK_m,                    setlayout,      {.v = &layouts[0]} },
  { MODKEY,            XK_t,                    setlayout,      {.v = &layouts[1]} },
  { MODKEY,            XK_f,                    setlayout,      {.v = &layouts[2]} },
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
