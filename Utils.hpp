#ifndef Common_h
#define Common_h

#define NUM_LEDS 768
#define PIN_LED 2

#define FRAMES_PER_SECOND 30

#define LED_COLUMNS 16
#define LED_ROWS 48
#define LED_ZIG_ZAG // undefine, if LED Matrix is not laid out in Zig Zag 

class Utils
{
public:
  static int getIndexFromPos( int col, int row );
};

#endif