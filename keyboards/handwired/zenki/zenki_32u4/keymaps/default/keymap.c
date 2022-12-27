#include QMK_KEYBOARD_H

enum custom_keycodes {
    DNF_PICK = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DNF_PICK:
        if (record->event.pressed) {
            send_string(SS_TAP(X_ENT) SS_DELAY(100) "//" SS_DELAY(100) SS_TAP(X_LSFT) SS_DELAY(100) "ydwp" SS_DELAY(100) SS_TAP(X_SPC) SS_DELAY(100) SS_TAP(X_LSFT) SS_DELAY(100) SS_TAP(X_ENT));
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_5x4(
    KC_NLCK,    KC_PSLS,      KC_PAST,          KC_PMNS,\
    KC_P7,      KC_P8,        KC_P9,            KC_NO,\
    KC_P4,      KC_P5,        KC_P6,            KC_PPLS,\
    KC_P1,      KC_P2,        KC_P3,            KC_NO,\
    KC_P0,      LT(1,KC_SPC), LT(2,KC_PDOT),    KC_PENT
  ),

  [1] = LAYOUT_ortho_5x4(
    RGB_VAI,    RGB_HUI,      RGB_SAI,    RGB_TOG,\
    RGB_VAD,    RGB_HUD,      RGB_SAD,    KC_NO,\
    RGB_RMOD,   KC_UP,        RGB_MOD,    RGB_M_P,\
    KC_LEFT,    KC_DOWN,      KC_RIGHT,   KC_NO,\
    DNF_PICK,   KC_TRNS,      KC_NO,      TG(1)
  ),

  [2] = LAYOUT_ortho_5x4(
    RESET,      KC_NO,        KC_NO,      KC_NO,\
    KC_BRIU,    KC_VOLU,      KC_NO,      KC_NO,\
    KC_NO,      KC_MUTE,      KC_NO,      KC_NO,\
    KC_BRID,    KC_VOLD,      KC_NO,      KC_NO,\
    KC_NO,      KC_NO,        KC_NO,      TG(2)
  )
};

