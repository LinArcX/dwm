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
    /* class    instance      title       tags mask     isfloating   monitor */
    { "Emacs",  "",           NULL,       4,            0,           -1 },
    { "st-256color",  "",     NULL,       0,            0,           -1 },
    { "Alacritty",  "",       NULL,       0,            0,           -1 },
    { "mpv",      NULL,       NULL,       0,            1,           -1 },
    { "Xephyr", "",           NULL,       0,            1,           -1 },
    { "", "Xephyr",           NULL,       0,            1,           -1 },
    { "Emulator", "",         NULL,       0,            1,           -1 },
    { "",   "Emulator",       NULL,       0,            1,           -1 },
    { "Brave-browser", "",    NULL,       2,            0,           -1 },
    { "nyxt", "",             NULL,       2,            0,           -1 },
    { "Tor Browser", "",      NULL,       2,            0,           -1 },
    { "Anki",        "",      NULL,       4,            0,           -1 },
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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define PrintScreenDWM    0x0000ff61

#define  POWER  "power.sh"
#define  SCREENSHOT  "screenshot.sh scr"
#define  WINSCREENSHOT  "screenshot.sh win"
#define  DWMPATH  "/home/linarcx/miso/dwm/scripts/"
#define  PATH_POWER  DWMPATH POWER
#define  PATH_SCREENSHOT DWMPATH SCREENSHOT
#define  PATH_WINSCREENSHOT DWMPATH WINSCREENSHOT

#define  COMMANDS  "commands.sh"
#define  CHANNELS  "channels.sh"
#define  POWERMANAGER  "power_manager.sh"
#define  DMENUPATH  "/home/linarcx/miso/dmenu/scripts/"
#define  PATH_COMMANDS DMENUPATH COMMANDS
#define  PATH_CHANNELS DMENUPATH CHANNELS
#define  PATH_POWERMANAGER DMENUPATH POWERMANAGER

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "sh", "-c", PATH_POWER };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *mutecmd[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "sset", "PCM", "5-", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "sset", "PCM", "5+", "unmute", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
  { MODKEY|ShiftMask,  XK_e,      spawn,          SHCMD(PATH_POWERMANAGER)},
  { MODKEY,            XK_r,      spawn,          SHCMD("alacritty -e lfcd.sh")},
  { MODKEY,            XK_Return, spawn,          {.v = termcmd }},
  { MODKEY,            XK_F1,     spawn,          SHCMD(PATH_COMMANDS)},
  { MODKEY,            XK_F2,     spawn,          SHCMD(PATH_CHANNELS)},
  { 0,                 XF86XK_AudioMute,          spawn,          SHCMD("amixer set Master toggle")},
  { 0,                 XF86XK_AudioRaiseVolume,   spawn,          SHCMD("amixer set Master 5%+")},
  { 0,                 XF86XK_AudioLowerVolume,   spawn,          SHCMD("amixer set Master 5%-")},
  { 0,                 PrintScreenDWM,            spawn,          SHCMD(PATH_SCREENSHOT)},
  { MODKEY,            XK_p,      spawn,          SHCMD(PATH_WINSCREENSHOT)},
  { MODKEY,            XK_b,      togglebar,      {0} },
  { MODKEY,            XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,            XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,            XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,            XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,            XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,            XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,            XK_Return, zoom,           {0} },
  { MODKEY,            XK_Tab,    view,           {0} },
  { MODKEY|ShiftMask,  XK_q,      killclient,     {0} },
  { MODKEY,            XK_m,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,            XK_t,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,            XK_f,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,            XK_space,  setlayout,      {0} },
  { MODKEY|ShiftMask,  XK_space,  togglefloating, {0} },
  { MODKEY,            XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,  XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,            XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,            XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,  XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,  XK_period, tagmon,         {.i = +1 } },
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
