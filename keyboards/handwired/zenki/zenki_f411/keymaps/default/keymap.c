/* Copyright 2021 burningbright
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#include "math.h"
#include "audio.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2
};

// Declare custom keycodes
enum custom_keycodes {
    MO_BASE = SAFE_RANGE,
    MUSIC_0,
    MUSIC_1,
    MUSIC_2,
    MUSIC_3,
    MUSIC_4,
    MUSIC_5,
  MACRO_TIMBRE_1,
  MACRO_TIMBRE_2,
  MACRO_TIMBRE_3,
  MACRO_TIMBRE_4,
  MACRO_TEMPO_U,
  MACRO_TEMPO_D,
  MACRO_TONE_DEFAULT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_NUM,     KC_PSLS,      KC_PAST,          KC_PMNS,\
        KC_P7,      KC_P8,        KC_P9,            KC_NO,\
        KC_P4,      KC_P5,        KC_P6,            KC_PPLS,\
        KC_P1,      KC_P2,        KC_P3,            KC_NO,\
        KC_NO,      LT(2,KC_P0),  LT(1,KC_PDOT),    KC_PENT
    ),
    [_FN1] = LAYOUT(
        RESET,      KC_CAPS,      KC_SCRL,    KC_NO,\
        CK_TOGG,    CK_UP,        CK_DOWN,    KC_NO,\
        MUSIC_0,    MUSIC_1,      MUSIC_2,    KC_NO,\
        MUSIC_3,    MUSIC_4,      MUSIC_5,    KC_NO,\
        KC_NO,      KC_NO,        KC_NO,      TG(1)
    ),
    [_FN2] = LAYOUT(
        MACRO_TIMBRE_1,      MACRO_TIMBRE_2,        MACRO_TIMBRE_3,      MACRO_TIMBRE_4,\
        MACRO_TEMPO_U,       MACRO_TEMPO_D,         MACRO_TONE_DEFAULT,  KC_NO,\
        MUSIC_0,    MUSIC_1,      MUSIC_2,    KC_NO,\
        MUSIC_3,    MUSIC_4,      MUSIC_5,    KC_NO,\
        KC_NO,      KC_NO,        KC_NO,      TG(2)
    )
};

#ifdef AUDIO_ENABLE
/* Title:            Happy Birthday to You
 * Author/Composer:  Kentucky, Mildred and Patty Hill
 * License:          Public Domain
 */
#define HAPPY_BIRTHDAY_TO_YOU QD_NOTE(_G4), E__NOTE(_G4), \
    Q__NOTE(_A4), Q__NOTE(_G4), Q__NOTE(_C5), \
    H__NOTE(_B4), QD_NOTE(_G4), E__NOTE(_G4), \
    Q__NOTE(_A4), Q__NOTE(_G4), Q__NOTE(_D5), \
    H__NOTE(_C5), QD_NOTE(_G4), E__NOTE(_G4), \
    Q__NOTE(_G5), Q__NOTE(_E5), Q__NOTE(_C5), \
    Q__NOTE(_B4), Q__NOTE(_A4), QD_NOTE(_F5), E__NOTE(_F5), \
    Q__NOTE(_E5), Q__NOTE(_C5), Q__NOTE(_D5), \
    H__NOTE(_C5),

#define HAPPY_BIRTHDAY_TO_YOU_D QD_NOTE(_A4), E__NOTE(_A4), \
    Q__NOTE(_B4), Q__NOTE(_A4), Q__NOTE(_D5), \
    H__NOTE(_CS4),QD_NOTE(_A4), E__NOTE(_A4), \
    Q__NOTE(_B4), Q__NOTE(_A4), Q__NOTE(_E5), \
    H__NOTE(_D5), QD_NOTE(_A4), E__NOTE(_A4), \
    Q__NOTE(_A5), Q__NOTE(_FS5),Q__NOTE(_D5), \
    Q__NOTE(_CS4),Q__NOTE(_B4), QD_NOTE(_G5), E__NOTE(_G5), \
    Q__NOTE(_FS5),Q__NOTE(_D5), Q__NOTE(_E5), \
    H__NOTE(_D5),

float caps_on[][2]       = SONG(CAPS_LOCK_ON_SOUND);
float caps_off[][2]      = SONG(CAPS_LOCK_OFF_SOUND);
float campanella[][2]    = SONG(CAMPANELLA);
float fantasie[][2]      = SONG(FANTASIE_IMPROMPTU);
float nocturne[][2]      = SONG(NOCTURNE_OP_9_NO_1);
float ussr[][2]          = SONG(USSR_ANTHEM);
float birthday[][2]      = SONG(HAPPY_BIRTHDAY_TO_YOU);
float birthday_d[][2]      = SONG(HAPPY_BIRTHDAY_TO_YOU_D);
#endif

bool led_update_user(led_t led_state) {
    #ifdef AUDIO_ENABLE
    static uint8_t caps_state = 0;
    if (caps_state != led_state.caps_lock) {
        led_state.caps_lock ? PLAY_SONG(caps_on) : PLAY_SONG(caps_off);
        caps_state = led_state.caps_lock;
    }
    #endif
    return true;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(B14, led_state.num_lock);
        writePin(B15, led_state.caps_lock);
        writePin(A6,  led_state.scroll_lock);
	writePin(A7,  timer_read() % 2);
    }
    return res;
}

// Runs every time a key is pressed or released
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Store the current modifier state in the variable for later reference
    switch (keycode) {
        case MUSIC_0:
            if (record->event.pressed) {
                PLAY_SONG(campanella);
            }
            break;
        case MUSIC_1:
            if (record->event.pressed) {
                PLAY_SONG(fantasie);
            }
            break;
        case MUSIC_2:
            if (record->event.pressed) {
                PLAY_SONG(nocturne);
            }
            break;
        case MUSIC_3:
            if (record->event.pressed) {
                PLAY_SONG(ussr);
            }
            break;
        case MUSIC_4:
            if (record->event.pressed) {
                PLAY_SONG(birthday);
            }
            break;
        case MUSIC_5:
            if (record->event.pressed) {
                PLAY_SONG(birthday_d);
            }
            break;
       case MACRO_TIMBRE_1:
            if (record->event.pressed) set_timbre(TIMBRE_12);
            break;

        case MACRO_TIMBRE_2:
            if (record->event.pressed) set_timbre(TIMBRE_25);
            break;

        case MACRO_TIMBRE_3:
            if (record->event.pressed) set_timbre(TIMBRE_50);
            break;

        case MACRO_TIMBRE_4:
            if (record->event.pressed) set_timbre(TIMBRE_75);
            break;

        case MACRO_TEMPO_U:
            if (record->event.pressed) increase_tempo(10);
            break;

        case MACRO_TEMPO_D:
            if (record->event.pressed) decrease_tempo(10);
            break;

        case MACRO_TONE_DEFAULT:
            if (record->event.pressed)
            {
                set_timbre(TIMBRE_DEFAULT);
                set_tempo(TEMPO_DEFAULT);
            }
            break;
    }
    return true;
}
