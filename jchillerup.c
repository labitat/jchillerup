#include <util/delay.h>
#include <arduino/pins.h>

#define LATCH 4
#define CLOCK 3
#define DATA  2

#define MAX 100

static void
shiftout(uint8_t v1, uint8_t v2, uint8_t v3)
{
	uint8_t mask;

	pin_low(LATCH);

	for (mask = 1; mask; mask <<= 1) {
		if (v1 & mask)
			pin_high(DATA);
		else
			pin_low(DATA);
		pin_high(CLOCK);
		pin_low(CLOCK);
	}

	for (mask = 1; mask; mask <<= 1) {
		if (v2 & mask)
			pin_high(DATA);
		else
			pin_low(DATA);
		pin_high(CLOCK);
		pin_low(CLOCK);
	}

	for (mask = 1; mask; mask <<= 1) {
		if (v3 & mask)
			pin_high(DATA);
		else
			pin_low(DATA);
		pin_high(CLOCK);
		pin_low(CLOCK);
	}

	pin_high(LATCH);
}

int __attribute__((noreturn))
main()
{
	int8_t dir = 1;
	uint8_t leds[24] = {
		0,   0,   0,   0,   0,   0,   0,   0,
		0,   0,   0,   0,   0,   0,   0,   0,
		0,   0,   0,   0,   0,   0,   0,   0
	};

	pin_mode_output(LATCH);
	pin_mode_output(CLOCK);
	pin_mode_output(DATA);

	pin_high(LATCH);
	pin_low(CLOCK);
	pin_high(DATA);

	while (1) {
		uint8_t i;
		uint8_t v1 = 0xFF;
		uint8_t v2 = 0xFF;
		uint8_t v3 = 0xFF;

		for (i = 0; i < MAX; i++) {
			uint8_t mask;
			uint8_t j = 0;

			for (mask = 1; mask; mask <<= 1) {
				if (i == leds[j++])
					v1 &= ~mask;
			}

			for (mask = 1; mask; mask <<= 1) {
				if (i == leds[j++])
					v2 &= ~mask;
			}

			for (mask = 1; mask; mask <<= 1) {
				if (i == leds[j++])
					v3 &= ~mask;
			}

			shiftout(v1, v2, v3);
			_delay_us(10);
		}

		leds[22] += dir;
		if (leds[22] == MAX - 1)
			dir = -dir;
		if (leds[22] == 0)
			dir = -dir;
	}
}
