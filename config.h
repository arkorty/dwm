/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const char *audioctl[] = {"/usr/bin/pavucontrol", NULL};
static const char *slockctl[] = {"/usr/local/bin/slock", NULL};
static const char *screenshot[] = {"/usr/local/bin/screencap", NULL};
// static const char *brightup[] = {"/usr/bin/xbacklight", "-inc", "5", NULL};
// static const char *brightdown[] = {"/usr/bin/xbacklight", "-dec", "5", NULL};
static const char *brightup[] = {"/usr/local/bin/backlightctl", "-u", NULL};
static const char *brightdown[] = {"/usr/local/bin/backlightctl", "-d", NULL};
// static const char *upvol[] = {"/usr/bin/pactl", "set-sink-volume", "0",
// "+5%", NULL}; static const char *downvol[] = {"/usr/bin/pactl",
// "set-sink-volume", "0", "-5%", NULL}; static const char *mutevol[] =
// {"/usr/bin/pactl", "set-sink-mute", "0", "toggle", NULL};
static const char *upvol[] = {"/usr/local/bin/volumectl", "-u", NULL};
static const char *downvol[] = {"/usr/local/bin/volumectl", "-d", NULL};
static const char *mutevol[] = {"/usr/local/bin/volumectl", "-m", NULL};
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const int showbar = 1;           /* 0 means no bar */
static const int topbar = 1;            /* 0 means bottom bar */
static const char *fonts[] = {"JetBrainsMono Nerd Font:size=9"};
static const char dmenufont[] = {"JetBrainsMono Nerd Font:size=9"};

/* base16 black metal */
#if 1
// static const char base00[] = "#000000";
static const char base00[] = "#171717";
static const char base01[] = "#121212";
static const char base02[] = "#222222";
// static const char base03[] = "#333333";
static const char base03[] = "#494949";
static const char base04[] = "#999999";
static const char base05[] = "#c1c1c1";
static const char base06[] = "#999999";
static const char base07[] = "#c1c1c1";
static const char base08[] = "#5f8787";
static const char base09[] = "#aaaaaa";
static const char base0A[] = "#a06666";
static const char base0B[] = "#dd9999";
static const char base0C[] = "#aaaaaa";
static const char base0D[] = "#888888";
static const char base0E[] = "#999999";
static const char base0F[] = "#444444";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {base05, base00, base0F},
    [SchemeSel] = {base05, base03, base0A},
};
#endif

/* nord */
#if 0
static const char col_gray1[] = "#2e3440";
static const char col_gray2[] = "#81a1c1";
static const char col_gray3[] = "#88c0d0";
static const char col_gray4[] = "#d8dee9";
static const char col_cyan[] = "#ebcb8b";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray4, col_gray1, col_gray3},
    [SchemeSel] = {col_gray1, col_gray2, col_cyan},
};
#endif

/* gruvbox */
#if 0
static const char col_gray1[] = "#282828";
static const char col_gray2[] = "#282828";
static const char col_gray3[] = "#ebdbb2";
static const char col_gray4[] = "#282828";
static const char col_cyan[] = "#ebdbb2";

static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};
#endif

/* tagging */
static const char *tags[] = {"term", "edit",  "file", "www", "docs",
                             "comm", "media", "misc", "misc"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class, instance, title, tags mask, iscentered, isfloating, monitor */
    {"Nitrogen", NULL, NULL, 0, 1, 1, -1},
    {"Alacritty", NULL, NULL, 0, 0, 0, -1},
    {"Nemo", NULL, NULL, 1 << 2, 0, 0, -1},
    {"Code", NULL, NULL, 1 << 1, 0, 0, -1},
    {"Pavucontrol", NULL, NULL, 0, 1, 1, -1},
    {"firefox", NULL, NULL, 1 << 3, 0, 0, -1},
    {"Spotify", NULL, NULL, 1 << 6, 0, 0, -1},
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
#define TAGKEYS(KEY, TAG)                                                      \
    {MODKEY, KEY, view, {.ui = 1 << TAG}},                                     \
        {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},             \
        {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                      \
        {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
    {                                                                          \
        .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                   \
    }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */

/* base16 black metal */
#if 1
static const char *dmenucmd[] = {
    "dmenu_run", "-m",   dmenumon, "-fn",  dmenufont, "-nb",  base00,
    "-nf",       base05, "-sb",    base08, "-sf",     base00, NULL};
#endif

/* nord */
#if 0
static const char *dmenucmd[] = {
    "dmenu_run", "-m",  dmenumon,  "-fn", dmenufont, "-nb", col_gray1, "-nf",
    col_gray4,   "-sb", col_gray2, "-sf", col_gray1, NULL};
#endif

static const char *termcmd[] = {"alacritty", NULL};

static Key keys[] = {
    /* modifie              rkey                        function argument */
    {0, XK_Print, spawn, {.v = screenshot}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightup}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = brightup}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = brightdown}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
    {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
    {MODKEY | ShiftMask, XK_a, spawn, {.v = audioctl}},
    {MODKEY | ShiftMask, XK_l, spawn, {.v = slockctl}},
    {MODKEY | ShiftMask, XK_f, togglefullscr, {0}},
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
