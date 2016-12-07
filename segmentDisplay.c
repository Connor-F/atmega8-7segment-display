#include "segmentDisplay.h"

/*
   sets up the control pins to ensure there is no
   output on the display to begin with
*/
void initSegmentDisplay(void)
{
	// ensure control pins are set for output (so they can be grounded)
	SEGMENT_CONTROL_DDR |= (SEGMENT_1_CONTROL_PIN | SEGMENT_2_CONTROL_PIN
			| SEGMENT_3_CONTROL_PIN | SEGMENT_4_CONTROL_PIN | SEGMENT_COLON_CONTROL_PIN);

	turnOffSegments();

	// set the led control pins as outputs
	LED_CONTROL_DDR |= (BOTTOM_LEFT_LED_PIN | BOTTOM_RIGHT_LED_PIN
			| BOTTOM_LED_PIN | TOP_LEFT_LED_PIN | TOP_RIGHT_LED_PIN
			| TOP_LED_PIN | MIDDLE_LED_PIN);

	turnOffLEDs();
}

/*
   helper function to turn off the segments on the display. This puts
   the segment control pins in a high state (no ground)
*/
static void turnOffSegments(void)
{
	// ensure control pins start off HIGH (so no segment is selected)
	SEGMENT_CONTROL_PORT |= (SEGMENT_1_CONTROL_PIN | SEGMENT_2_CONTROL_PIN
			| SEGMENT_3_CONTROL_PIN | SEGMENT_4_CONTROL_PIN | SEGMENT_COLON_CONTROL_PIN);
}

/*
   helper function to turn off the pins that control the
   display LEDs
*/
static void turnOffLEDs(void)
{
	// ensure led control pins are set to LOW
	LED_CONTROL_PORT &= ~(BOTTOM_LEFT_LED_PIN | BOTTOM_RIGHT_LED_PIN
			| BOTTOM_LED_PIN | TOP_LEFT_LED_PIN | TOP_RIGHT_LED_PIN
			| TOP_LED_PIN | MIDDLE_LED_PIN | COLON_LED_PIN);
}

/*
   displays a number in a given segment
	Param: seg -> the segment to display the number in, e.g. SEGMENT_1
		   number -> the value to display in the segment
	Returns: 0 on success
			 1 if provided segment or number was out of range
*/
uint8_t displayWriteNumber(segment_t seg, uint8_t number)
{
	if(seg >= SEGMENT_T_MAX || number > 9) // can only display 0-9 per segment
		return 1;

	turnOffSegments();
	turnOffLEDs();

	switch(number) // set the corresponding output pins to HIGH to draw the number provided
	{
		case 0:
			LED_CONTROL_PORT |= (TOP_LED_PIN | TOP_LEFT_LED_PIN | TOP_RIGHT_LED_PIN
					| BOTTOM_LEFT_LED_PIN | BOTTOM_LED_PIN | BOTTOM_RIGHT_LED_PIN);
			break;
		case 1:
			LED_CONTROL_PORT |= (TOP_RIGHT_LED_PIN | BOTTOM_RIGHT_LED_PIN);
			break;
		case 2:
			LED_CONTROL_PORT |= (TOP_LED_PIN | TOP_RIGHT_LED_PIN | MIDDLE_LED_PIN
					| BOTTOM_LEFT_LED_PIN | BOTTOM_LED_PIN);
			break;
		case 3:
			LED_CONTROL_PORT |= (TOP_LED_PIN | TOP_RIGHT_LED_PIN | MIDDLE_LED_PIN
					| BOTTOM_RIGHT_LED_PIN | BOTTOM_LED_PIN);
			break;
		case 4:
			LED_CONTROL_PORT |= (TOP_LEFT_LED_PIN | MIDDLE_LED_PIN | TOP_RIGHT_LED_PIN
					| BOTTOM_RIGHT_LED_PIN);
			break;
		case 5:
			LED_CONTROL_PORT |= (TOP_LED_PIN | TOP_LEFT_LED_PIN | MIDDLE_LED_PIN
					| BOTTOM_RIGHT_LED_PIN | BOTTOM_LED_PIN);
			break;
		case 6:
			LED_CONTROL_PORT |= (TOP_LED_PIN | TOP_LEFT_LED_PIN | MIDDLE_LED_PIN
					| BOTTOM_LEFT_LED_PIN | BOTTOM_RIGHT_LED_PIN | BOTTOM_LED_PIN);
			break;
		case 7:
			LED_CONTROL_PORT |= (TOP_LED_PIN | TOP_RIGHT_LED_PIN | BOTTOM_RIGHT_LED_PIN);
			break;
		case 8:
			LED_CONTROL_PORT |= (TOP_LEFT_LED_PIN | TOP_LED_PIN | TOP_RIGHT_LED_PIN 
					| MIDDLE_LED_PIN | BOTTOM_RIGHT_LED_PIN | BOTTOM_LEFT_LED_PIN | BOTTOM_LED_PIN);
			break;
		case 9:
			LED_CONTROL_PORT |= (TOP_LEFT_LED_PIN | TOP_LED_PIN | TOP_RIGHT_LED_PIN 
					| MIDDLE_LED_PIN | BOTTOM_RIGHT_LED_PIN | BOTTOM_LED_PIN);
			break;
		default: // will never be reached
			break;
	}

	if(seg == SEGMENT_1) // ground the segment control pin so the LEDs have a complete circuit
		SEGMENT_CONTROL_PORT &= ~SEGMENT_1_CONTROL_PIN;
	else if(seg == SEGMENT_2)
		SEGMENT_CONTROL_PORT &= ~SEGMENT_2_CONTROL_PIN;
	else if(seg == SEGMENT_3)
		SEGMENT_CONTROL_PORT &= ~SEGMENT_3_CONTROL_PIN;
	else if(seg == SEGMENT_4)
		SEGMENT_CONTROL_PORT &= ~SEGMENT_4_CONTROL_PIN;

	return 0;
}

/*
   illuminates the middle colon on the segment display
*/
void displayWriteColon(void)
{
	turnOffSegments();
	turnOffLEDs();

	SEGMENT_CONTROL_PORT &= ~SEGMENT_COLON_CONTROL_PIN;
	LED_CONTROL_PORT |= COLON_LED_PIN;
}
