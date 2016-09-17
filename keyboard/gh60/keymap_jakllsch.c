#include "keymap_common.h"
#include "action_util.h"

enum keymap_id {
        NATIVE_KM = 0,
        DVORAK_KM,
        DVORAKFN_KM,
#if 0
        D2Q_KM,
#endif
};

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NATIVE_KM] = KEYMAP(
        FN4, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,  \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,FN1, RSFT, \
        CAPS,LGUI,LALT,          SPC,                GRV, RALT,RGUI,FN0, RCTL),
    [DVORAK_KM] = KEYMAP(
        FN4, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,BSPC, \
        TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL, BSLS, \
        LCTL,A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,NUHS,ENT,  \
        LSFT,NUBS,SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,   FN1, RSFT, \
        CAPS,LGUI,LALT,          SPC,                GRV, RALT,RGUI,FN0, RCTL),
    [DVORAKFN_KM] = KEYMAP(
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL, \
        TRNS,HOME,PGDN,PGUP,END, FN2, WFWD,WHOM,CALC,WREF,RGHT,PSCR,SLCK,PAUS, \
        TRNS,LEFT,DOWN,UP,  RGHT,INS, FN3, LEFT,MPRV,MPLY,MNXT,MSTP,TRNS,TRNS, \
        TRNS,TRNS,INS, DEL, DOWN,UP,  NLCK,WBAK,MUTE,VOLD,VOLU,APP, TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,TRNS,TRNS),
#if 0
    [D2Q_KM] = KEYMAP(
        FN4, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   QUOT,RBRC,BSPC, \
        TAB, X,   COMM,D,   O,   K,   T,   F,   G,   S,   R,   MINS,EQL, BSLS, \
        LCTL,A,   SCLN,H,   Y,   U,   J,   C,   V,   P,   Z,   Q,   NUHS,ENT,  \
        LSFT,NUBS,SLSH,B,   I,   DOT, N,   L,   M,   W,   E,   LBRC,FN1, RSFT, \
        CAPS,LGUI,LALT,          SPC,                GRV, RALT,RGUI,FN0, RCTL),
#endif
};

enum action_function_id {
       TRICKY_ESC_FN = 0,
};

/*
 * Fn action definition
 */
const action_t PROGMEM fn_actions[] = {
    [FN_INDEX(KC_FN0)] = ACTION_LAYER_TAP_KEY(DVORAKFN_KM, KC_APP),
    [FN_INDEX(KC_FN1)] = ACTION_LAYER_MOMENTARY(DVORAKFN_KM),
    [FN_INDEX(KC_FN2)] = ACTION_DEFAULT_LAYER_SET(NATIVE_KM),
    [FN_INDEX(KC_FN3)] = ACTION_DEFAULT_LAYER_SET(DVORAK_KM),
    [FN_INDEX(KC_FN4)] = ACTION_FUNCTION(TRICKY_ESC_FN),
};
    //[] = ACTION_DEFAULT_LAYER_SET(D2Q_KM),

#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    static uint8_t tricky_esc_registered;
    switch (id) {
        case TRICKY_ESC_FN:
            if (record->event.pressed) {
                if (get_mods() & MODS_SHIFT_MASK) {
                    tricky_esc_registered = KC_GRV;
                }
                else {
                    tricky_esc_registered = KC_ESC;
                }
                register_code(tricky_esc_registered);
                send_keyboard_report();
            }
            else {
                unregister_code(tricky_esc_registered);
                send_keyboard_report();
            }
            break;
    }
}
