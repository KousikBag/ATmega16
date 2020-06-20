//Generating Multiple Frequencies
/*
 * This example uses CTC mode of 8-bit Timer/Counter2 for generating various
 * audio frequencies on OC2/PD7 (Pin 21).
 * Hence, Buzzer/Speaker is to be connected between OC2/PD7 (Pin 21) & GND.
 */

#include <avr/io.h>
#include <util/delay.h>

#define HUMAN_AUDIBLE_MAX_FREQ 20000

#define PRESCALER (2 << CS20) /* Prescaler N = 8 */
#define N 8
#define MAX_FREQ (F_CPU / (2 * N)) /* F_CPU / (2 * N * (1 + (OCR2 = 0))) */
#define MIN_FREQ (F_CPU / (2 * N * 256)) /* F_CPU / (2 * N * (1 + (OCR2 = 255))) */

void set_frequency(unsigned long freq)
{
	if (freq < MIN_FREQ)
	{
		freq = MIN_FREQ;
	} else if (freq > MAX_FREQ)
	{
		freq = MAX_FREQ;
	}
	/* f = MAX_FREQ / (1 + OCR2), i.e. OCR2 = MAX_FREQ / f - 1; */
	OCR2 = MAX_FREQ / freq - 1;
}
void init_timer(unsigned long freq)
{
	DDRD |= (1 << PD7); // OC2 is PD7 - setting it as output

	set_frequency(freq);

	/*
	 * Setting the Timer/Counter2 in CTC (Clear Timer on Compare) (non-PWM) mode.
	 * Toggling on Match to generate square wave for a particular frequency,
	 * as per the prescaler and OCR2 setting.
	 * Output would come on OC2/PD7 (Pin 21).
	 */
	TCCR2 = (1 << WGM21) | (0 << WGM20) | (1 << COM20) | PRESCALER;
}
void stop_timer(void)
{
	TCCR2 = 0;
}

int main(void)
{
	unsigned long freq = MIN_FREQ;

	init_timer(freq);

	while (1)
	{
		_delay_ms(1500);
		freq += MIN_FREQ;
		if (freq > HUMAN_AUDIBLE_MAX_FREQ)
		{
			freq = MIN_FREQ;
		}
		set_frequency(freq);
	}

	stop_timer();

	return 0;
}
