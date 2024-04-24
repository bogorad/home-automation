// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include "print.h"

#include "manna-harbour_miryoku.h"
#include "features/achordion.h"

////////////////////////////////////////////////
// Define a structure to hold layer-tap information
typedef struct {
    bool     is_active;
    bool     command_sent;
    uint16_t timer;
} layer_tap_t;

  // Initialize structure instance for holding state
layer_tap_t my_lt = {false, false, 0};

// system init
void keyboard_post_init_user(void) {
  debug_enable=false;
  debug_matrix=false;
  debug_keyboard=false;
};

// Additional Features double tap guard
// tap-dance
enum {
    U_TD_BOOT,
//    U_TD_RUS_YO,
//    U_TD_RUS_HA,
//    U_TD_RUS_S_H,
#define MIRYOKU_X(LAYER, STRING) U_TD_U_##LAYER,
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

// reset keyboard into BOOT mode
void u_td_fn_boot(tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
    reset_keyboard();
  }
}

//// tap-dance for Cyryllic: ш э ё
//void dance_sh_ae_yo(tap_dance_state_t *state, void *user_data) {
//    switch (state->count) {
//        case 1:
//            SEND_STRING("i"); // ш
//            break;
//        case 2:
//            SEND_STRING("'"); // э
//            break;
//        case 3:
//            SEND_STRING("`"); // ё
//            break;
//    }
//}

#define MIRYOKU_X(LAYER, STRING) \
void u_td_fn_U_##LAYER(tap_dance_state_t *state, void *user_data) { \
  if (state->count == 2) { \
    default_layer_set((layer_state_t)1 << U_##LAYER); \
  } \
}
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X

tap_dance_action_t tap_dance_actions[] = {
    [U_TD_BOOT] = ACTION_TAP_DANCE_FN(u_td_fn_boot),
//    [U_TD_RUS_YO] = ACTION_TAP_DANCE_FN(dance_sh_ae_yo),
//    [U_TD_RUS_HA]  = ACTION_TAP_DANCE_DOUBLE(KC_O,KC_LBRC),
//    [U_TD_RUS_S_H] = ACTION_TAP_DANCE_DOUBLE(KC_M,KC_RBRC),
#define MIRYOKU_X(LAYER, STRING) [U_TD_U_##LAYER] = ACTION_TAP_DANCE_FN(u_td_fn_U_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

enum custom_keycodes {
  LANG_ENG = SAFE_RANGE, // Ensure these don't conflict with existing keycodes
  LANG_RUS,
  VIM_SAVE,
  VIM_CMD,
  LT_SYM_ENT,
  LT_NUM_BSPC,
  MY_COMMA,
  MY_DOT,
  MY_QUESTION,
  MY_SLASH,
};

// keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#define MIRYOKU_X(LAYER, STRING) [U_##LAYER] = U_MACRO_VA_ARGS(MIRYOKU_LAYERMAPPING_##LAYER, MIRYOKU_LAYER_##LAYER),
MIRYOKU_LAYER_LIST
#undef MIRYOKU_X
};

////////////////////////////////////////////////////////////////////
// This switches to English but only when LT-key is pressed and another key it tapped.
//
// Function to handle layer-tap logic
void process_layer_tap(uint16_t keycode, uint16_t layer, keyrecord_t *record) {
    if (record->event.pressed) {
        // Key was pressed - start timer.
        my_lt.timer = timer_read();
        my_lt.is_active = true;
        layer_on(layer);
        dprintf("lt: pressed!\n");
    } else { // Key was released
        // Was it a tap?
        if (my_lt.is_active && timer_elapsed(my_lt.timer) < TAPPING_TERM) {
            tap_code(keycode);
            dprintf("lt: tapped!\n");
        }
        layer_off(layer);
        // Only retore win kbd layout if it was switched.
        if (my_lt.command_sent) {
          // Tell Windows we're still in Cyrillic
          SEND_STRING(SS_LSFT(SS_LALT("1")));
          // Clear flag.
          my_lt.command_sent = false;
          dprintf("lt: sent SA(1) to windows!\n");
        }
        my_lt.is_active = false;
        dprintf("lt: released!\n");
    }
}

////////////////////////////////////////////////////////////////////
// shift functions

const key_override_t capsword_key_override = ko_make_basic(MOD_MASK_SHIFT, CW_TOGG, KC_CAPS);

const key_override_t **key_overrides = (const key_override_t *[]){
    &capsword_key_override,
    NULL
};


///////////////////////////////////////////////////////////////////////////
// 4
const uint16_t PROGMEM combo_caps_word[]  = {KC_B,    KC_J,    COMBO_END};
const uint16_t PROGMEM switch_to_rus[]    = {KC_D,    KC_H,    COMBO_END};
const uint16_t PROGMEM just_meta[]        = {LGUI_T(KC_A),
                                             LGUI_T(KC_O),     COMBO_END};
const uint16_t PROGMEM buttons_oneshot[]  = {KC_Z,    KC_SLSH, COMBO_END};
// enter/undo/cut/copy/paste 5
const uint16_t PROGMEM my_enter[]         = {KC_U,    KC_Y,    COMBO_END};
const uint16_t PROGMEM my_undo[]          = {KC_Z,    KC_X,    COMBO_END};
const uint16_t PROGMEM my_cut[]           = {KC_X,    KC_C,    COMBO_END};
const uint16_t PROGMEM my_copy[]          = {KC_C,    KC_D,    COMBO_END};
const uint16_t PROGMEM my_paste[]         = {KC_D,    KC_V,    COMBO_END};
// vim 2
const uint16_t PROGMEM vim_save[]         = {KC_W,    KC_F,    COMBO_END};
const uint16_t PROGMEM vim_cmd[]          = {KC_F,    KC_P,    COMBO_END};
// ,.? 3
const uint16_t PROGMEM my_comma[]         = {KC_H,    KC_COMM, COMBO_END};
const uint16_t PROGMEM my_dot[]           = {KC_COMM, KC_DOT,  COMBO_END};
const uint16_t PROGMEM my_question[]      = {KC_DOT,  KC_SLSH, COMBO_END};
///////////////////////////////////////////////////////////////////////////

combo_t key_combos[COMBO_COUNT] = {
  COMBO(combo_caps_word,  QK_CAPS_WORD_TOGGLE),
  COMBO(switch_to_rus,    LANG_RUS),
  COMBO(just_meta,        KC_LGUI),
  COMBO(buttons_oneshot,  OSL(U_BUTTON)),
  //
  COMBO(my_enter,         KC_ENTER),
  COMBO(my_undo,          C(KC_Z)),
  COMBO(my_cut,           C(KC_X)),
  COMBO(my_copy,          U_CPY),
  COMBO(my_paste,         S(KC_INS)),
  //
  COMBO(vim_save,         VIM_SAVE),
  COMBO(vim_cmd,          VIM_CMD),
  //
  COMBO(my_comma,         MY_COMMA),
  COMBO(my_dot,           MY_DOT),
  COMBO(my_question,      MY_QUESTION),
};

//////////////// here we switch languages
//
// define fallback first
void switch_to_english(void) {
  // Save mods.
  uint8_t mod_state = get_mods();
  // Clear mods so Windows doesn't get confused.
  clear_mods();
  // Ctrl+Alt+0 sent to host
  SEND_STRING(SS_LSFT(SS_LALT("0")));
  // Switch to default layer.
  layer_move(U_BASE);
  // debug
  dprint("Switched to English!\n");
  // Restore mods.
  set_mods(mod_state);
};

#define RUS_LAYER_TIMEOUT 5000  // timeout in milliseconds

void switch_to_russian(void) {
  // switch back to English if already in Russian mode
  if (get_highest_layer(layer_state) == U_EXTRA) {
    dprint("Russian active! Switching back to English\n");
    switch_to_english();
  }
  else
  {
    // Save mods.
    uint8_t mod_state = get_mods();
    // Clear mods so Windows doesn't get confused.
    clear_mods();
    // Ctrl+Alt+1 sent to host
    SEND_STRING(SS_LSFT(SS_LALT("1")));
    // Switch to Cyrillic-friendly layer.
    layer_move(U_EXTRA);
    // debug
    dprint("Switched to Russian!\n");
    // Restore mods.
    set_mods(mod_state);
  };
};

void matrix_scan_user(void) {
  // achordion
  achordion_task();
  //
  // this resets current language to English after <timeout> if Russian was active
  if (get_highest_layer(layer_state) == U_EXTRA) {
    if (last_input_activity_elapsed() > RUS_LAYER_TIMEOUT) {
      switch_to_english();
    }
  }
}

/////////////////////////////////////////////////
void send_in_english(char* msg){
  bool russian_active = (get_highest_layer(layer_state) == U_EXTRA);
  dprintf("sie: Russian active: %d\n", russian_active);
  if (russian_active)
    switch_to_english();
  // send whatever
  SEND_STRING(msg);
  // restore russian if it was active
  if (russian_active)
    switch_to_russian();
}

/////////////////////////////////////////////////
// macro processor etc
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t mod_state = get_mods();
  //
  // only print to HID console when debugging is on
  dprintf("KL: kc: 0x%04X, col: %3u, row: %3u, pressed: %u, time: %5u, int: %u, count: %u layer: %u\n",
          keycode,
          record->event.key.col,
          record->event.key.row,
          record->event.pressed,
          record->event.time,
          record->tap.interrupted,
          record->tap.count,
          get_highest_layer(layer_state));
  //
  // achordion
  if (!process_achordion(keycode, record)) { return false; }
  //
  // check for specific keycodes
  switch (keycode) {
    //
    // fake keys first
    case LANG_ENG:
      if (record->event.pressed)
        switch_to_english();
      return false; // Skip further processing
        //
    case LANG_RUS:
      if (record->event.pressed)
        switch_to_russian();
      return false; // Skip further processing
        //
    case VIM_SAVE:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)":w"SS_TAP(X_ENTER));
        dprint("vim->saved!\n");
      }
      return false; // Skip further processing
        //
    case VIM_CMD:
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_ESCAPE)":");
        dprint("vim->command.\n");
      }
      return false; // Skip further processing
        //
        // special consideration for TAB & ESCAPE & digits
    case LT(U_MOUSE,KC_TAB):
    case LT(U_MEDIA,KC_ESC):
      // only operate if pressed
      if (record->event.pressed &&
          // Ignore if held
          record->tap.count     &&
          // Check if the current layer is U_EXTRA
          layer_state_cmp(layer_state, U_EXTRA) &&
          // And any of the modifiers are active
          (mod_state & (MOD_BIT(KC_LALT) |
                        MOD_BIT(KC_LSFT) |
                        MOD_BIT(KC_LCTL) |
                        MOD_BIT(KC_LGUI)
                       )))
      {
        switch_to_english();
      };
      return true; // Continue normal tab processing
      //
    case MY_COMMA:
      if (record->event.pressed) {
        send_in_english(",");
      }
      return false; // Skip all further processing of this key
      //
    case MY_DOT:
      if (record->event.pressed) {
        send_in_english(".");
      }
      return false; // Skip all further processing of this key
      //
    case MY_QUESTION:
      if (record->event.pressed) {
        send_in_english("?");
      }
      return false; // Skip all further processing of this key
      //
    case MY_SLASH:
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT)
          send_in_english("?");
        else
          send_in_english("/");
      }
      return false; // Skip all further processing of this key
      //
    case LT_SYM_ENT:
      process_layer_tap(KC_ENT, U_SYM, record);
      return false; // Skip all further processing of this key
      //
    case LT_NUM_BSPC:
      process_layer_tap(KC_BSPC, U_NUM, record);
      return false; // Skip all further processing of this key
      //
    default:
      if (my_lt.is_active && record->event.pressed) {
        // Only switch win kbd layout if it has not been switched.
        if (!my_lt.command_sent) {
          // Custom function called when any key is pressed while MY_LT is active
          my_lt.command_sent = true;
          SEND_STRING(SS_LSFT(SS_LALT("0")));
          dprintf("lt: sent SA(0) to windows!\n");
        }
        return true;  // Allow the key press to be handled normally by QMK
      }
      break;
  } // done with specific keys
  //
  return true;
}
