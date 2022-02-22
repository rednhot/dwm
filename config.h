/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>
#define PrtSc    0x0000ff61

#define ICONSIZE 16   /* icon size */
#define ICONSPACING 5 /* space between icon and title */


/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
    "JetBrains Mono:size=12",
    "JoyPixels:pixelsize=14:antialias=true:autohint=true",
    "Font Awesome 5 Free:pixelsize=16",
    "Font Awesome 5 Brands:pixelsize=16",
    "Symbola:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrains Mono:size=12";

#include "/home/mathway/.cache/wal/colors-wal-dwm.h"

/* tagging */
static const char *tags[] = {"", "", "", "", "", "", "", "", "" };
static const char *tagsalt[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const int momentaryalttags = 1; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                              instance    title       tags mask     isfloating   monitor */
    { "imaginary_program_name",               NULL,       NULL,       1 << 1,       0,           -1 },
    { "discord",                              NULL,       NULL,       1 << 3,       0,           -1 },
    { "TelegramDesktop",                      NULL,       NULL,       1 << 3,       0,           -1 },
    { "Firefox",                              NULL,       NULL,       1 << 2,       0,           -1 },
    { "ghidra-Ghidra",                        NULL,       NULL,       1 << 6,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)						\
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

/* misc commands */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
static const char *termcmd[]  = { "st", "-z", "16", NULL };
static const char *dumbtermcmd[]  = { "st_dumb", "-z", "16", NULL };
static const char *browsercmd[] = { "www-browser", NULL };
static const char *telegramcmd[] = { "telegram-desktop", NULL };
static const char *discordcmd[] = { "discord", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-z", "16", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *fmcmd[] = { "pcmanfm", NULL };
static const char *share_filecmd[] = { "share", NULL };
static const char *getfilepathcmd[] = { "getfile", NULL };
static const char *postselcmd[] = { "share_selection", NULL };

/* volume management commands */
static const char *upvol[] = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *downvol[] = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *mute[] = { "amixer", "-q", "-D", "pulse", "sset", "Master", "toggle", NULL };

/* power management */
static const char *haltcmd[] = { "sudo", "shutdown", "-h", "now", NULL };
static const char *rebootcmd[] = { "sudo", "shutdown", "-r", "now", NULL };
static const char *suspendcmd[] = { "sudo", "s2ram", NULL };
static const char *brightupcmd[] = { "sudo", "brightmod", "+10%", NULL };
static const char *brightdowncmd[]= { "sudo", "brightmod", "-10%", NULL };

/* screenshots */
static const char *scrn_full_diskcmd[] = {"screenshot", "-d", "/home/mathway/pics", "-f", NULL};
static const char *scrn_part_diskcmd[] = {"screenshot", "-d", "/home/mathway/pics", "-p", NULL};
static const char *scrn_full_clipcmd[] = {"screenshot", "-c", "-f", NULL};
static const char *scrn_part_clipcmd[] = {"screenshot", "-c", "-p", NULL};




#include "shift-tools.c"
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_e,      spawn,          {.v = dumbtermcmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = telegramcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = discordcmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = fmcmd } },
	{ MODKEY|ShiftMask,          XK_backslash, spawn,          {.v = share_filecmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = getfilepathcmd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = postselcmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_h,      spawn,          {.v = haltcmd } },
	{ MODKEY|ShiftMask|ControlMask, XK_r,      spawn,          {.v = rebootcmd } },	
	{ MODKEY|ShiftMask|ControlMask, XK_s,      spawn,          {.v = suspendcmd } },
        { 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = upvol } },
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = downvol } },
	{ 0,              XF86XK_AudioMute,        spawn,          {.v = mute } },
	{ ControlMask,                  PrtSc,     spawn,          {.v = scrn_full_diskcmd} },
	{ ControlMask|ShiftMask,        PrtSc,     spawn,          {.v = scrn_part_diskcmd} },
	{ 0,                            PrtSc,     spawn,          {.v = scrn_full_clipcmd} },
	{ ShiftMask,                    PrtSc,     spawn,          {.v = scrn_part_clipcmd} },
	{ 0,             XF86XK_MonBrightnessUp,  spawn,           {.v = brightupcmd } },
	{ 0,             XF86XK_MonBrightnessDown,spawn,           {.v = brightdowncmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,		XK_p,      shiftboth,      { .i = -1 }	},
	{ MODKEY|ShiftMask,             XK_n,      shiftboth,      { .i = +1 }	},
	{ MODKEY|ControlMask,		XK_p,      shiftswaptags,  { .i = -1 }	},
	{ MODKEY|ControlMask,		XK_n,      shiftswaptags,  { .i = +1 }	},
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Down,   movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Up,     movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,                     XK_F4,     killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_n,	   shiftview,      { .i = +1 } },
	{ MODKEY,                       XK_p,	   shiftview,      { .i = -1 } },
	{ MODKEY,                       XK_q,      togglealttag,   {0} },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_9,                      9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
