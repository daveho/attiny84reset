// Generate a power-on reset pulse using an attiny84.

#include <avr/interrupt.h>
#define F_CPU 800000UL
#include <util/delay.h>
#include <stdint.h>

// GPIOs on port A
// Pin 0 is the reset output.
// Pin 1 is the momentary normally open manual reset button:
//  when the button is pressed, pin 1 is connected to ground.
// Pin 2 is a LED that is lit when the firmware starts running.
//   This is useful becaues you can see the duration of the reset
//   pulse (500 ms).

#define RST (1 << 0)
#define SW  (1 << 1)
#define PWR (1 << 2)

int main(){
  DDRA = RST|PWR; // enable output on A0 and A2

  PORTA |= SW; // enable pullup on A1, for reset switch

  // Light the LED on A2 just so we can see
  // when the reset pulse is being generated
  PORTA |= PWR;

  // Generate a 500 ms reset pulse
  PORTA &= ~RST;
  _delay_ms(500);
  PORTA |= RST;

  // Monitor switch: when pressed, input will go low, and
  // we'll re-assert reset.  Use a counter to debounce
  // the signal.
  uint8_t btn_last = PINA & SW;
  uint8_t count = 0;
  while (1) {
    uint8_t btn_now = PINA & SW;

    if (btn_now != btn_last) {
      count = 0;
    } else if (count < 255) {
      count++;
    }

    if (count > 10) {
      if (btn_now == 0) {
        // pressed, generate manual reset
        PORTA &= ~RST;
      } else {
        // not pressed
        PORTA |= RST;
      }
    }

    btn_last = btn_now;

    _delay_us(100); // delay .1ms
  }
}
