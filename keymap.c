/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

static bool muted = false;
static bool group_ctrl = false;
static bool preset_ctrl = false;
static bool active_groups[5] = {true, false, false, false, false};
static int lightmode = 0;
static int layer = 0;

enum custom_keycodes {
    START_LIGHTING = SAFE_RANGE,
    EXIT_LAYER,
    MUTE,
    LIGHT1,
    LIGHT2,
    LIGHT3,
    LIGHT4,
    LIGHT5,
    ENCODER1,
    ENCODER2,
    ENCODER3,
};

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

void toggle_group(int group) {
    if (active_groups[group]) {
        active_groups[group] = false;
    } else {
        active_groups[group] = true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode){
        case START_LIGHTING:
            if (record->event.pressed) {
                tap_code(KC_F15);
                layer_clear();
                layer_on(1);
                layer = 1;
            }
            break;
        case EXIT_LAYER:
            if (record->event.pressed) {
                tap_code16(LALT(KC_F18));
                if (group_ctrl) {
                    group_ctrl = false;
                } else if (preset_ctrl) {
                    preset_ctrl = false;
                } else {
                    layer_clear();
                    layer_on(0);
                    layer = 0;
                    matrix_init_user();
                }
            }
            break;
        case MUTE:
            if (record->event.pressed) {
                if (muted) {
                    muted = false;
                    tap_code(KC_F23);
                } else {
                    muted = true;
                    tap_code(KC_F24);
                }
            }
        case ENCODER1:
            if (record->event.pressed) {
                tap_code(KC_F19);
                if (lightmode != 0) {
                    lightmode = 0;
                }
            }
            break;
        case ENCODER2:
            if (record->event.pressed) {
                tap_code(KC_F20);
                if (lightmode != 1) {
                    lightmode = 1;
                }
            }
            break;
        case ENCODER3:
            if (record->event.pressed) {
                tap_code(KC_F21);
                if (lightmode != 2) {
                    lightmode = 2;
                }
            }
            break;
        case LIGHT1:
            if (record->event.pressed) {
                tap_code16(LALT(KC_F13));
                if (group_ctrl) {
                    toggle_group(0);
                } else if (!preset_ctrl) {
                    group_ctrl = true;
                }
            }
            break;
        case LIGHT2:
            if (record->event.pressed) {
                tap_code16(LALT(KC_F14));
                if (group_ctrl) {
                    toggle_group(1);
                }
            }
            break;
        case LIGHT3:
            if (record->event.pressed) {
                tap_code16(LALT(KC_F15));
                if (group_ctrl) {
                    toggle_group(2);
                }
            }
            break;
        case LIGHT4:
            if (record->event.pressed) {
                tap_code16(LALT(KC_F16));
                if (group_ctrl) {
                    toggle_group(3);
                } else if (!preset_ctrl) {
                    preset_ctrl = true;
                }
            }
            break;
        case LIGHT5:
            if (record->event.pressed) {
                tap_code16(LALT(KC_F17));
                if (group_ctrl) {
                    toggle_group(4);
                }
            }
        break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        LWIN(KC_ESCAPE), START_LIGHTING, KC_MUTE,
        KC_BSPACE, KC_F16  , MUTE,
        LCTL(KC_C), LCTL(KC_V), KC_ENTER
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        ENCODER1, ENCODER2, ENCODER3,
        LIGHT1, LIGHT2, LIGHT3,
        LIGHT4, LIGHT5, EXIT_LAYER
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (clockwise) {
            tap_code16(LWIN(KC_EQUAL));
        } else {
            tap_code16(LWIN(KC_MINUS));
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            tap_code(KC_F13);
        } else {
            tap_code(KC_F14);
        }
    }
    else if (index == _RIGHT) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}

void rgb_matrix_indicators_user(void) {
    if (layer == 1) {
        if (group_ctrl) {
            rgb_matrix_sethsv(127, 255, 100);
        } else if (preset_ctrl) {
            rgb_matrix_sethsv(201, 255, 100);
        } else {
            if (lightmode == 0) {
                rgb_matrix_sethsv(43, 255, 100);
            } else if (lightmode == 1) {
                rgb_matrix_sethsv(0, 255, 100);
            } else {
                rgb_matrix_sethsv(85, 255, 100);
            }
        }

        for (int i = 0; i < 5; i++) {
            if (active_groups[i]) {
                rgb_matrix_set_color(i+3, 100, 100, 0);
            } else {
                rgb_matrix_set_color(i+3, 0, 0, 0);
            }
        }
    } else {
        rgb_matrix_sethsv(128, 255, 100);
        if (muted) {
            rgb_matrix_set_color(5, 100, 0, 0);
        }
    }
}

void matrix_init_user(void) {
    // rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_NONE);
    rgb_matrix_sethsv(128, 255, 100);
}