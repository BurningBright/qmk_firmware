/* Copyright 2022 burningbright
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

#pragma once

#include "config_common.h"

#define VENDOR_ID    0x1210
#define PRODUCT_ID   0x3270
#define DEVICE_VER   0x0001
#define MANUFACTURER stm32
#define PRODUCT      blackpill_f411

// Both controllers draw 100 mA or less
//#define USB_MAX_POWER_CONSUMPTION 100

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 20

/* pin distribution */
#define MATRIX_ROW_PINS { C13 }
#define MATRIX_COL_PINS { B12, B13, B1, B10, B3, A15, A5, A4, B5, B4, A3, A2, B7, B6, A1, A0, B9, B8, C15, C14 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* Audio */
#define AUDIO_PIN A10
#define AUDIO_PWM_PAL_MODE 1
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL 3
#define AUDIO_STATE_TIMER GPTD4

/* RGB LED */
#define RGB_DI_PIN B1
#define RGBLED_NUM 4
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE

/* B1 config */
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 5


/* LED indicators */
#define LED_NUM_LOCK_PIN    B14
#define LED_CAPS_LOCK_PIN   B15
#define LED_SCROLL_LOCK_PIN A6
#define LED_COMPOSE_PIN     A7

/* Trackpoint */
#define PS2_CLOCK_PIN  A8
#define PS2_DATA_PIN   A9
#define PS2_MOUSE_X_MULTIPLIER  3
#define PS2_MOUSE_Y_MULTIPLIER  3
#define PS2_MOUSE_V_MULTIPLIER  1

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
