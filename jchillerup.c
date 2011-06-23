#include <util/delay.h>
#include <arduino/pins.h>

#define LATCH 4
#define CLOCK 3
#define DATA  2
#define OE 8
#define RESET 9

#define MAX 255
#define MAX_R 50
#define MAX_G 100
#define MAX_B 100

uint8_t leds[48] = {
  0,   0,   0,   
  0,   0,   0,   
  0,   0,   0,   
  0,   0,   0, 
  0,   0,   0,  
  0,   0,   0,
  0,   0,   0,   
  0,   0,   0,
  0,   0,   0,  
  0,   0,   0,   
  0,   0,   0,   
  0,   0,   0, 
  0,   0,   0,   
  0,   0,   0,   
  0,   0,   0,   
  0,   0,   0
};

uint8_t ledmask[24] = {
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1,
  1,   1,   1,   1,   1,   1,   1,   1
};

static void
shiftout(uint8_t v1, uint8_t v2, uint8_t v3, uint8_t v4, uint8_t v5, uint8_t v6)
{
	uint8_t mask;
	int i=0;
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

	for (mask = 1; mask; mask <<= 1) {
		if (v4 & mask)
			pin_high(DATA);
		else
			pin_low(DATA);
		pin_high(CLOCK);
		pin_low(CLOCK);
	}

	for (mask = 1; mask; mask <<= 1) {
		if (v5 & mask)
			pin_high(DATA);
		else
			pin_low(DATA);
		pin_high(CLOCK);
		pin_low(CLOCK);
	}

	for (mask = 1; mask; mask <<= 1) {
		if (v6 & mask)
			pin_high(DATA);
		else
			pin_low(DATA);
		pin_high(CLOCK);
		pin_low(CLOCK);
	}

	pin_high(LATCH);
}

static void pwm() {
  uint8_t i;
  uint8_t v1 = 0xFF;
  uint8_t v2 = 0xFF;
  uint8_t v3 = 0xFF;
  uint8_t v4 = 0xFF;
  uint8_t v5 = 0xFF;
  uint8_t v6 = 0xFF;
  
  for (i = 0; i < MAX; i++) {
    uint8_t mask;
    uint8_t j = 0;
    
    for (mask = 1; mask; mask <<= 1) {
      if (i == leds[j])
	v1 &= ~mask;
      if (i == leds[j+8])
	v2 &= ~mask;
      if (i == leds[j+16])
	v3 &= ~mask;
      if (i == leds[j+24])
	v4 &= ~mask;
      if (i == leds[j+32])
	v5 &= ~mask;
      if (i == leds[j+40])
	v6 &= ~mask;

      j++;
    }
    
    shiftout(v1, v2, v3, v4, v5, v6);
  } 
}


int __attribute__((noreturn))
main()
{
  int8_t dir = 1;
  int state  = 0;
  int i;
  
  pin_mode_output(LATCH);
  pin_mode_output(CLOCK);
  pin_mode_output(DATA);
  pin_mode_output(OE);
  pin_mode_output(RESET);
  
  pin_high(LATCH);
  pin_low(CLOCK);
  pin_high(DATA);
  pin_low(OE);
  pin_high(RESET);
  

  for(i = 2; i<48; i+=3) {
    leds[i-1] = 200;
    //    leds[i-2] = 50;
    //    leds[i-2] = 35;
  }
  

  while (1) {
    int i =0;

    pwm(48);
  }
}


