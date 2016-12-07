#ifndef GUARD_SEGMENT_DISPLAY_H
#define GUARD_SEGMENT_DISPLAY_H

#include <avr/io.h>

// the following definitions represent the pins on the mcu 
// that control which segment of the display is currently selected.
// display segments are selected by grounding the pin. A large resistor
// between the displays segment control pin and the mcu should be used,
// as current flows into the display then out of the selected control
// pin, therefore into the mcu. Using an ATMega328 at 3.3V with a 330 Ohm
// resistor on each control pin ensures current is limited whilst still
// having a readable display
#define SEGMENT_CONTROL_DDR DDRC
#define SEGMENT_CONTROL_PORT PORTC

#define SEGMENT_1_CONTROL_PIN (1 << PC0)
#define SEGMENT_2_CONTROL_PIN (1 << PC1)
#define SEGMENT_COLON_CONTROL_PIN (1 << PC1) // same as above
#define SEGMENT_3_CONTROL_PIN (1 << PC3)
#define SEGMENT_4_CONTROL_PIN (1 << PC4)

// the following definitions represent the pins on the mcu that
// control the individual segment LEDs. After grounding the pin
// associated with the desired segment, these pins can be set
// to high to light up the needed LED
#define LED_CONTROL_DDR DDRB
#define LED_CONTROL_PORT PORTB

#define BOTTOM_LEFT_LED_PIN (1 << PB0)
#define BOTTOM_RIGHT_LED_PIN (1 << PB1)
#define TOP_LEFT_LED_PIN (1 << PB2)
#define TOP_RIGHT_LED_PIN (1 << PB3)
#define MIDDLE_LED_PIN (1 << PB4)
#define TOP_LED_PIN (1 << PB5)
#define BOTTOM_LED_PIN (1 << PB6)
#define COLON_LED_PIN (1 << PB7)

// used to select a segment to display info on
typedef enum
{
	SEGMENT_1,
	SEGMENT_2,
	SEGMENT_3,
	SEGMENT_4,
	SEGMENT_T_MAX
} segment_t;

void initSegmentDisplay(void);

// functions for displaying info
uint8_t displayWriteNumber(segment_t, uint8_t);
void displayWriteColon(void);

static void turnOffSegments(void);
static void turnOffLEDs(void);

#endif
