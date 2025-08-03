// ###########################

#define MIRYOKU_LAYER_BASE \
KC_Q,              KC_W,              KC_F,              KC_P,              KC_B,              KC_J,              KC_L,              KC_U,              KC_Y,              KC_QUOT,           \
LGUI_T(KC_A),      LALT_T(KC_R),      LCTL_T(KC_S),      LSFT_T(KC_T),      KC_G,              KC_M,              LSFT_T(KC_N),      LCTL_T(KC_E),      LALT_T(KC_I),      LGUI_T(KC_O),      \
KC_Z,              KC_X,              KC_C,              KC_D,              KC_V,              KC_K,              KC_H,              KC_COMM,           KC_DOT,            KC_SLSH,           \
U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT(U_SYM,KC_ENT),  LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_NAV \
TD(U_TD_BOOT),     U_NA,              TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   KC_LCBR,           KC_RCBR,           KC_HOME,           KC_UP,             KC_END,            KC_PGUP,           \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           KC_LBRC,           KC_RBRC,           KC_LEFT,           KC_DOWN,           KC_RIGHT,          KC_PGDN,           \
DB_TOGG,           U_NA,              KC_LEFT,           KC_RIGHT,          KC_CIRCUMFLEX,     KC_DLR,            KC_F23,            C(KC_F23),         A(KC_F23),         G(KC_F23),         \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              U_NA,              KC_DEL,            KC_INS,            U_NP,              U_NP

#define MIRYOKU_LAYER_MOUSE \
TD(U_TD_BOOT),     U_NA,              TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA,              LANG_ENG,          KC_WH_L,           KC_MS_U,           KC_WH_R,           KC_WH_U,           \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              LANG_RUS,          KC_MS_L,           KC_MS_D,           KC_MS_R,           KC_WH_D,           \
DB_TOGG,           KC_MS_ACCEL0,      KC_MS_ACCEL1,      KC_MS_ACCEL2,      KC_DEL,            U_NA,              U_NA,              U_NA,              U_NA,              U_NA,              \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_BTN2,           KC_BTN1,           KC_BTN3,           U_NP,              U_NP

#define MIRYOKU_LAYER_NUM \
KC_MINS,           KC_7,              KC_8,              KC_9,              KC_PLUS,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  U_NA,              TD(U_TD_BOOT),     \
KC_COLN,           KC_4,              KC_5,              KC_6,              KC_EQUAL,          U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_DLR,            KC_1,              KC_2,              KC_3,              KC_SLSH,           U_NA,              KC_BACKSPACE,      KC_TAB,            KC_CAPS_LOCK,      U_NA,              \
U_NP,              U_NP,              KC_DOT,            KC_0,              KC_MINS,           U_NA,              U_NA,              U_NA,              U_NP,              U_NP

#define MIRYOKU_LAYER_SYM \
KC_EXCLAIM,        KC_AT,             KC_HASH,           KC_DOLLAR,         KC_PERCENT,        KC_CIRCUMFLEX,     KC_AMPERSAND,      KC_ASTERISK,       KC_LEFT_PAREN,     KC_RIGHT_PAREN,    \
KC_PIPE,           KC_TILDE,          KC_DQUO,           KC_COLON,          KC_ASTERISK,       U_NP,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_BACKSLASH,      KC_GRAVE,          KC_QUOT,           KC_SEMICOLON,      KC_SLSH,           U_NP,              KC_BACKSPACE,      KC_TAB,            KC_CAPS_LOCK,      KC_BACKSLASH,      \
U_NP,              U_NP,              KC_LPRN,           KC_RPRN,           KC_UNDERSCORE,     U_NA,              U_NA,              U_NA,              U_NP,              U_NP

#define MIRYOKU_LAYER_MEDIA \
TD(U_TD_BOOT),     U_NA,              TD(U_TD_U_EXTRA),  TD(U_TD_U_BASE),   U_NA,              U_NA,              KC_LBRC,           KC_GRAVE,          KC_QUOT,           U_NA,              \
KC_LGUI,           KC_LALT,           KC_LCTL,           KC_LSFT,           U_NA,              U_NU,              KC_MPRV,           U_NA,              KC_MNXT,           U_NA,              \
U_NA,              KC_ALGR,           TD(U_TD_U_FUN),    TD(U_TD_U_MEDIA),  U_NA,              OU_AUTO,           KC_RBRC,           KC_LBRC,           KC_DOT,            KC_GRAVE,          \
U_NP,              U_NP,              U_NA,              U_NA,              U_NA,              KC_MSTP,           KC_MPLY,           KC_MUTE,           U_NP,              U_NP

#define MIRYOKU_LAYER_FUN \
KC_F12,            KC_F7,             KC_F8,             KC_F9,             KC_PSCR,           U_NA,              TD(U_TD_U_BASE),   TD(U_TD_U_EXTRA),  U_NA,              TD(U_TD_BOOT),     \
KC_F11,            KC_F4,             KC_F5,             KC_F6,             KC_SCRL,           U_NA,              KC_LSFT,           KC_LCTL,           KC_LALT,           KC_LGUI,           \
KC_F10,            KC_F1,             KC_F2,             KC_F3,             LCTL(LALT(LGUI(KC_F23))),U_NA,        KC_BACKSPACE,      KC_TAB,            KC_CAPS_LOCK,      U_NA,              \
U_NP,              U_NP,              KC_APP,            KC_SPC,            KC_TAB,            U_NA,              U_NA,              U_NA,              U_NP,              U_NP

// redefine QWERTY so it calls the correct symbols layer we've just defined
#define MIRYOKU_LAYER_EXTRA \
KC_Q,              KC_W,              KC_E,              KC_R,              KC_T,              KC_Y,              KC_U,              KC_I,              KC_O,              KC_P,              \
LGUI_T(KC_A),      LALT_T(KC_S),      LCTL_T(KC_D),      LSFT_T(KC_F),      KC_G,              KC_H,              LSFT_T(KC_J),      LCTL_T(KC_K),      LALT_T(KC_L),      LGUI_T(KC_SCLN),   \
KC_Z,              KC_X,              KC_C,              KC_V,              KC_B,              KC_N,              KC_M,              KC_COMMA,          MY_DOT,            MY_SLASH,          \
U_NP,              U_NP,              LT(U_MEDIA,KC_ESC),LT(U_NAV,KC_SPC),  LT(U_MOUSE,KC_TAB),LT_SYM_ENT,        LT_NUM_BSPC,       LT(U_FUN,KC_DEL),  U_NP,              U_NP

#define MIRYOKU_LAYER_BUTTON \
LCTL(LALT(LGUI(KC_Q))), LCTL(LALT(LGUI(KC_W))), LCTL(LALT(LGUI(KC_F))), LCTL(LALT(LGUI(KC_P))), LCTL(LALT(LGUI(KC_B))),   LCTL(LALT(LGUI(KC_J))), LCTL(LALT(LGUI(KC_L))),  LCTL(LALT(LGUI(KC_U))),    LCTL(LALT(LGUI(KC_Y))),   LCTL(LALT(LGUI(KC_QUOT))), \
LCTL(LALT(LGUI(KC_A))), LCTL(LALT(LGUI(KC_R))), LCTL(LALT(LGUI(KC_S))), LCTL(LALT(LGUI(KC_T))), LCTL(LALT(LGUI(KC_G))),   LCTL(LALT(LGUI(KC_M))), LCTL(LALT(LGUI(KC_N))),  LCTL(LALT(LGUI(KC_E))),    LCTL(LALT(LGUI(KC_I))),   LCTL(LALT(LGUI(KC_O))),    \
LCTL(LALT(LGUI(KC_Z))), LCTL(LALT(LGUI(KC_X))), LCTL(LALT(LGUI(KC_C))), LCTL(LALT(LGUI(KC_D))), LCTL(LALT(LGUI(KC_V))),   LCTL(LALT(LGUI(KC_K))), LCTL(LALT(LGUI(KC_H))),  LCTL(LALT(LGUI(KC_COMM))), LCTL(LALT(LGUI(KC_DOT))), LCTL(LALT(LGUI(KC_SLSH))), \
U_NP,                   U_NP,                   U_NP,                   U_NP,                   U_NP,                     U_NP,                   U_NP,                    U_NP,                      U_NP,                     U_NP


// redefine layer definition table to include the new layer
#define MIRYOKU_LAYER_LIST \
MIRYOKU_X(BASE,   "Base") \
MIRYOKU_X(EXTRA,  "Extra") \
MIRYOKU_X(BUTTON, "Button") \
MIRYOKU_X(NAV,    "Nav") \
MIRYOKU_X(MOUSE,  "Mouse") \
MIRYOKU_X(MEDIA,  "Media") \
MIRYOKU_X(NUM,    "Num") \
MIRYOKU_X(SYM,    "Sym") \
MIRYOKU_X(FUN,    "Fun")

// removed layer U_TAP, remapping references
#define U_TAP U_NUM

// for now; can't use other options with win/arm64
//#define UNICODE_SELECTED_MODES UNICODE_MODE_WINDOWS
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE
#define UNICODE_KEY_WINC KC_APPLICATION

#define COMBO_COUNT 14

#define ACHORDION_STREAK

#define CAPS_WORD_IDLE_TIMEOUT 3000  // 3 seconds.
#define COMBO_ONLY_FROM_LAYER 0

