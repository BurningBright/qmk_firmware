/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "digitizer.h"
#include "math.h"

// macro declare
enum macro_keycodes {
    // select a line
    FN_0 = SAFE_RANGE,
    FN_1,
    FN_2,
    FN_3,
    FN_4,
    FN_5,
    FN_6,
    FN_7,
    FN_8,
    FN_9,
    FN_10,
    FN_11,
    FN_12,
    FN_13,
    PWD_0,
    PWD_1,
    PWD_2,
    PWD_3,
    CMD_0,
    CMD_1,
    CMD_2,
    CMD_3,
    CMD_4,
    CMD_5
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: plain Qwerty without layer switching
     *
     * ,----.    ,-------------------. ,-------------------. ,-------------------.  ,--------------.
     * | Esc|    | F1 | F2 | F3 | F4 | | F5 | F6 | F7 | F8 | | F9 | F10| F11| F12|  | TG1|PULL |G(L)| 
     * `----'    `-------------------' `-------------------' `-------------------'  `--------------'
     * ,-------------------------------------------------------------------------.  ,--------------.  ,-------------------.
     * |   `|   1|   2|   3|   4|   5|   6|   7|   8|   9|   0|   -|   =|     Bsp|  | Ins| Hom| PgU|  | NmL|   /|   *|   -| 
     * |-------------------------------------------------------------------------|  |--------------|  | ------------------| 
     * | Tab  |   Q|   W|   E|   R|   T|   Y|   U|   I|   O|   P|   [|   ]|   \  |  | Del| End| PgD|  |   7|   8|   9|   +| 
     * |-------------------------------------------------------------------------|  `--------------'  |--------------|    | 
     * | MO1   |   A|   S|   D|   F|   G|   H|   J|   K|   L|   ;|   '|    Return|                    |   4|   5|   6|   +| 
     * |-------------------------------------------------------------------------|       ,----.       |-------------------| 
     * | Shift    |   Z|   X|   C|   V|   B|   N|   M|   ,|   ,|   /| Shift      |       | Up |       |   1|   2|   3|    | 
     * |-------------------------------------------------------------------------|  ,--------------.  |--------------|    | 
     * | Ctl| Gui| Alt|             Space                    |C(v)|C(c)|MO1| Ctl|  |Lef | Dow| Rig|  |        0|   .| Ent| 
     * `-------------------------------------------------------------------------'  `--------------'  `-------------------'
     */
    [0] = LAYOUT_ansi(
        KC_ESC,                      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,        KC_F10,   KC_F11,    KC_F12,       TG(1),    C(S(KC_L)),  G(KC_L),
        KC_GRV,         KC_1,        KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,   KC_8,    KC_9,    KC_0,         KC_MINS,  KC_EQL,    KC_BSPC,      KC_INS,   KC_HOME,     KC_PGUP,            KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,         KC_Q,        KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,         KC_LBRC,  KC_RBRC,   KC_BSLS,      KC_DEL,   KC_END,      KC_PGDN,            KC_P7,   KC_P8,   KC_P9,
        MO(1),          KC_A,        KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN,      LT(1, KC_QUOT),      KC_ENT,                                                  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT,        KC_Z,        KC_X,    KC_C,    KC_V,    KC_B,    KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,                           KC_RSFT,                KC_UP,                           KC_P1,   KC_P2,   KC_P3,
        KC_LCTL,        KC_LGUI,     KC_LALT,                   KC_SPC,                                    C(KC_V),      C(KC_C),  MO(1),     KC_RCTL,      KC_LEFT,  KC_DOWN,     KC_RGHT,            KC_P0,            KC_PDOT, KC_PENT
    ),

    /* 1: control mouse/arrow/function Layer
     *
     * ,----.    ,-------------------. ,-------------------. ,-------------------.  ,--------------.
     * |▒▒▒▒|    |CMD0|CMD1|CMD2|CMD3| |CMD4|CMD5|BRIU|BRID| |MUTE|VOLU|VOLD|FN10|  |TRS |TRS |TRS | 
     * `----'    `-------------------' `-------------------' `-------------------'  `--------------'
     * ,-------------------------------------------------------------------------.  ,--------------.  ,-------------------.
     * |████|PWD0|PWD1|PWD2|PWD3|    |    |    |    |    |    |    |    |     TRS|  |TRS |TRS |TRS |  |ACL0|ACL1|ACL2|    | 
     * |-------------------------------------------------------------------------|  |--------------|  | ------------------| 
     * |CapsL |FN6 |FN7 |FN8 | DEL|BSPC|BSPC|DEL |FN12|FN11|FN10|    |    |   TRS|  |TRS |TRS |TRS |  |    |    |    |    | 
     * |-------------------------------------------------------------------------|  `--------------'  |--------------|    | 
     * |TRS    |LEFT|DOWN|  UP|RGHT|ENT | ENT|LEFT|  UP|DOWN|RGHT|    |       TRS|                    |    | MSU|    |    | 
     * |-------------------------------------------------------------------------|       ,----.       |-------------------| 
     * |TRS       |FN1 |FN2 |FN3 |FN4 |FN5 |FN9 |    |HOME|END | FN0|        C(H)|       |WHU |       | MSL| MSD| MSR|    | 
     * |-------------------------------------------------------------------------|  ,--------------.  |--------------|    | 
     * |TRS |    |TRS |             TRS                      |TRS |TRS |TRS |C(F)|  |WHL |WHD |WHR |  |   BT1   | BT2|    | 
     * `-------------------------------------------------------------------------'  `--------------'  `-------------------'
     */
    [1] = LAYOUT_ansi(
        RESET,                         CMD_0,      CMD_1,      CMD_2,      CMD_3,     CMD_4,   CMD_5,    KC_BRIU,  KC_BRID,  KC_MUTE,       KC_VOLU,  KC_VOLD,  FN_10,      KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_NO,           PWD_0,        PWD_1,      PWD_2,      PWD_3,      KC_NO,     KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,         KC_NO,    KC_NO,    KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_ACL0,  KC_ACL1,  KC_ACL2,  KC_NO,
        KC_CAPS,         FN_6,         FN_7,       FN_8,       KC_DEL,     KC_BSPC,   KC_BSPC, KC_DEL,   FN_12,    FN_11,    FN_10,         KC_NO,    KC_NO,    KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_NO,    KC_NO,    KC_NO,
        KC_TRNS,         KC_LEFT,      KC_DOWN,    KC_UP,      KC_RGHT,    KC_ENT,    KC_ENT,  KC_LEFT,  KC_UP,    KC_DOWN,  KC_RGHT,       KC_NO,              KC_TRNS,                                         KC_NO,    KC_MS_U,  KC_NO,    KC_NO,
        KC_TRNS,         FN_1,         FN_2,       FN_3,       FN_4,       FN_5,      FN_9,   KC_NO,    KC_HOME,  KC_END,   FN_0,                              C(KC_H),              KC_WH_U,                   KC_MS_L,  KC_MS_D,  KC_MS_R,
        KC_TRNS,         KC_NO,        KC_TRNS,                KC_TRNS,                                            KC_TRNS,  KC_TRNS,       KC_TRNS,            C(KC_F),    KC_WH_L,  KC_WH_D,  KC_WH_R,         KC_BTN1,            KC_BTN2,  KC_NO
    ),

};

static void select_aline(void) {
    SEND_STRING(
        SS_TAP(X_END)
        SS_DELAY(10)
        SS_DOWN(X_LSFT)
        SS_DELAY(10)
        SS_TAP(X_HOME)
        SS_DELAY(10)
        SS_UP(X_LSFT));
}

static void select_to_home(void) {
    SEND_STRING(
        SS_DOWN(X_LSFT)
        SS_DELAY(10)
        SS_TAP(X_HOME)
        SS_DELAY(10)
        SS_UP(X_LSFT));
}

static void select_to_end(void) {
    SEND_STRING(
        SS_DOWN(X_LSFT)
        SS_DELAY(10)
        SS_TAP(X_END)
        SS_DELAY(10)
        SS_UP(X_LSFT));
}

static void ctrl_x(void) {
    SEND_STRING(
        SS_DELAY(10)
        SS_DOWN(X_LCTL)
        SS_DELAY(10)
        SS_TAP(X_X)
        SS_DELAY(10)
        SS_UP(X_LCTL));
}

static void ctrl_c(void) {
    SEND_STRING(
        SS_DELAY(10)
        SS_DOWN(X_LCTL)
        SS_DELAY(10)
        SS_TAP(X_C)
        SS_DELAY(10)
        SS_UP(X_LCTL));
}

static void ctrl_v(void) {
    SEND_STRING(
        SS_DELAY(10)
        SS_DOWN(X_LCTL)
        SS_DELAY(10)
        SS_TAP(X_V)
        SS_DELAY(10)
        SS_UP(X_LCTL));
}

bool digitizerToggled = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case FN_0:
            if (record->event.pressed) {
                // selects a line
                select_aline();
            }
            break;

	case FN_1:
            if (record->event.pressed) {
		// select a line and delete
                select_aline();
                SEND_STRING(SS_DELAY(10) SS_TAP(X_BSPC));
            }
            break;
        case FN_2:
            if (record->event.pressed) {
                // select a line and cut
                select_aline();
                ctrl_x();
            }
            break;
        case FN_3:
            if (record->event.pressed) {
                // select a line and copy
                select_aline();
                ctrl_c();
            }
            break;
        case FN_4:
            if (record->event.pressed) {
                // select a line and paste
                select_aline();
                ctrl_v();
            }
            break;

        case FN_5:
            if (record->event.pressed) {
                // select to home and delete
                select_to_home();
                SEND_STRING(SS_DELAY(10) SS_TAP(X_BSPC));
            }
            break;
        case FN_6:
            if (record->event.pressed) {
                // select to home and cut
                select_to_home();
                ctrl_x();
            }
            break;
        case FN_7:
            if (record->event.pressed) {
                // select to home and copy
                select_to_home();
                ctrl_c();
            }
            break;
        case FN_8:
            if (record->event.pressed) {
                // select to home and paste
                select_to_home();
                ctrl_v();
            }
            break;

        case FN_9:
            if (record->event.pressed) {
                // select to end and delete
                select_to_end();
                SEND_STRING(SS_DELAY(10) SS_TAP(X_BSPC));
            }
            break;
        case FN_10:
            if (record->event.pressed) {
                // select to end and cut
                select_to_end();
                ctrl_x();
            }
            break;
        case FN_11:
            if (record->event.pressed) {
                // select to home and copy
                select_to_end();
                ctrl_c();
            }
            break;
        case FN_12:
            if (record->event.pressed) {
                // select to home and paste
                select_to_end();
                ctrl_v();
            }
            break;

        case FN_13:
            if (record->event.pressed) {
                digitizer_t digitizer;
                digitizer.x         = 0.5 - 0.2 * cos(timer_read() / 250. / 6.28);
                digitizer.y         = 0.5 - 0.2 * sin(timer_read() / 250. / 6.28);
                digitizer.tipswitch = 0;
                digitizer.inrange   = 1;
                digitizer_set_report(digitizer);
            }
            break;

        case PWD_0:
            if (record->event.pressed) {
                SEND_STRING("chenguang.lin");
            }
            break;

        case PWD_1:
            if (record->event.pressed) {
                SEND_STRING("Leonn0105495");
            }
            break;

        case PWD_2:
            if (record->event.pressed) {
                SEND_STRING("Lcg0105495");
            }
            break;

        case PWD_3:
            if (record->event.pressed) {
            SEND_STRING("Hello world");
            }
            break;

        case CMD_0:
            if (record->event.pressed) {
                // linus thread
                SEND_STRING("ps -ef|grep ");
            }
            break;

        case CMD_1:
            if (record->event.pressed) {
                // net status
                SEND_STRING("netstat -tunlp");
            }
            break;

        case CMD_2:
            if (record->event.pressed) {
                // find content
                SEND_STRING("find -type f | xargs grep -iP ");
            }
            break;

        case CMD_3:
            if (record->event.pressed) {
                // docker thread
                SEND_STRING("127.0.0.1");
            }
            break;
        case CMD_4:
            if (record->event.pressed) {
                // docker log
                SEND_STRING("docker ps -a");
            }
            break;
        case CMD_5:
            if (record->event.pressed) {
                // docker log
                SEND_STRING("docker logs -f --tail=10 ");
            }
            break;

    }
    return true;
    
};

