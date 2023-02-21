/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const char *audioctl[] = {"/usr/bin/pavucontrol", NULL};
static const char *slockctl[] = {"/usr/local/bin/slock", NULL};
static const char *screenshot[] = {"/usr/local/bin/scrnctl", "/home/ark/Pictures/Screenshots/%Y-%m-%d-%T-screenshot.png", NULL};
// static const char *brightup[] = {"/usr/bin/xbacklight", "-inc", "5", NULL};
// static const char *brightdown[] = {"/usr/bin/xbacklight", "-dec", "5", NULL};
static const char *brightup[] = {"/usr/local/bin/brictl", "-u", NULL};
static const char *brightdown[] = {"/usr/local/bin/brictl", "-d", NULL};
// static const char *upvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "+5%", NULL};
// static const char *downvol[] = {"/usr/bin/pactl", "set-sink-volume", "0", "-5%", NULL};
// static const char *mutevol[] = {"/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL};
static const char *upvol[] = {"/usr/local/bin/volctl", "-u", NULL};
static const char *downvol[] = {"/usr/local/bin/volctl", "-d", NULL};
static const char *mutevol[] = {"/usr/local/bin/volctl", "-m", NULL};
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=9"};
static const char dmenufont[] = {"JetBrainsMono Nerd Font:size=9"};

// onedark colorscheme
// static const char norm_fg[] = "#abb2bf";
// static const char norm_bg[] = "#282c34";
// static const char norm_border[] = "#abb2bf";
//
// static const char sel_fg[] = "#282c34";
// static const char sel_bg[] = "#98c379";
// static const char sel_border[] = "#e5c07b";
//
// static const char *colors[][3] = {
//    /*               fg           bg         border                         */
//    [SchemeNorm] = {norm_fg, norm_bg, norm_border}, // unfocused wins
//    [SchemeSel] = {sel_fg, sel_bg, sel_border},     // the focused win
//};

static const char background[] = "#1e1e2e";
static const char bg_alt[] = "#181825";
static const char foreground[] = "#cdd6f4";
static const char cyan[] = "#89dceb";
static const char green[] = "#a6e3a1";
static const char orange[] = "#fab387";
static const char pink[] = "#f5c2e7";
static const char purple[] = "#cba6f7";
static const char red[] = "#f38ba8";
static const char yellow[] = "#f9e2af";
static const char blue[] = "#89b4fa";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {foreground, background, background},
    [SchemeSel] = {background, green, orange},
};

// everforest colorscheme
// static const char norm_bg[] = "#2f383e";
// static const char norm_border[] = "#2f383e";
// static const char norm_fg[] = "#d8caac";
// static const char sel_fg[] = "#2f383e";
// static const char sel_bg[] = "#a7c080";
// static const char sel_border[] = "#a7c080";
//
// static const char *colors[][3] = {
//    /*               fg         bg         border   */
//    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
//    [SchemeSel] = {sel_fg, sel_bg, sel_border},
//};

// gruvbox colorscheme
// static const char norm_fg[] = "#bdae93";
// static const char norm_bg[] = "#282828";
// static const char norm_border[] = "#504945";
// static const char sel_bg[] = "#504945";
// static const char sel_fg[] = "#ebdbb2";
// static const char sel_border[] = "#ebdbb2";
// static const char *colors[][3] = {
//    /*               fg         bg         border   */
//    [SchemeNorm] = {norm_fg, norm_bg, norm_border},
//    [SchemeSel] = {sel_fg, sel_bg, sel_border},
//};

// dracula colorscheme
// static const char norm_fg[] = "#ff6e67";
// static const char norm_bg[] = "#282a36";
// static const char norm_border[] = "#ff6e67";
//
// static const char sel_fg[] = "#bfbfbf";
// static const char sel_bg[] = "#282a36";
// static const char sel_border[] = "#dfdfdd";
//
// static const char *colors[][3] = {
//    /*               fg           bg         border                         */
//    [SchemeNorm] = {norm_fg, norm_bg, norm_border}, // unfocused wins
//    [SchemeSel] = {sel_fg, sel_bg, sel_border},     // the focused win
//};

/* tagging */
static const char *tags[] = {"", "", "", "", "", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class, instance, title, tags mask, iscentered, isfloating, monitor */
    {"Pavucontrol", NULL, NULL, 0, 1, 1, -1},
    {"Nitrogen", NULL, NULL, 0, 1, 1, -1},
    {"Gimp", NULL, NULL, 0, 0, 0, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY, TAG)                                          \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                         \
        {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}}, \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},          \
        {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                           \
    {                                                        \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
    }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", background,
    "-nf", foreground, "-sb", background, "-sf", foreground, NULL};
static const char *termcmd[] = {"alacritty", NULL};

static Key keys[] = {
    /* modifie              rkey                        function argument */
    {0, XK_Print, spawn, {.v = screenshot}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightup}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightdown}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {MODKEY | ShiftMask, XK_a, spawn, {.v = audioctl}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = slockctl}},
    {MODKEY, XK_p, spawn, {.v = dmenucmd}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, togglebar, {0}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
