/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include <avr/io.h>
#include "stdint.h"
#include "led.h"

#ifdef BOOTMAGIC_ENABLE
#include "keymap.h"
extern keymap_config_t keymap_config;
#endif

#define K30_LED_DDR DDRB
#define K30_LED_PORT PORTB
#define K30_LED_PIN PINB
#define K30_LED_BIT PB2

#define K58_LED_DDR DDRB
#define K58_LED_PORT PORTB
#define K58_LED_PIN PINB
#define K58_LED_BIT PB6

void led_set(uint8_t usb_led)
{
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
#if defined(GH60_REV_CHN) || defined(GH60_REV_KC60)
        if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
            // output high
            DDRB |= (1<<6);
            PORTB |= (1<<6);
        } else
#endif
        {
            // output low
            DDRB |= (1<<2);
            PORTB &= ~(1<<2);
        }
    } else {
#if defined(GH60_REV_CHN) || defined(GH60_REV_KC60)
        if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
            DDRB |= (1<<6);
            PORTB &= ~(1<<6);
        } else
#endif
        {
            // Hi-Z
            DDRB &= ~(1<<2);
            PORTB &= ~(1<<2);
        }
    }
}
