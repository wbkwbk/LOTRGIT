#ifndef WS2812Wrapper_h
#define WS2812Wrapper_h


#include <WS2812FX.h>

class WS2812Wrapper{
	public: 
		WS2812Wrapper(uint16_t num_leds, uint8_t pin, neoPixelType type, long runDuration);
    void setAnimduration(long runDuration);
    void startAnim();
    void check();
	private:
		WS2812FX ws2812fxInstance;
    long animStarttime;
    long animRunDuration;
};

#endif