#ifndef WS2812Wrapper_h
#define WS2812Wrapper_h


#include <WS2812FX.h>

class WS2812Wrapper{
	public: 
		WS2812Wrapper(uint16_t num_leds, uint8_t pin, neoPixelType type);
	private:
		WS2812FX ws2812fxInstance;
};

#endif