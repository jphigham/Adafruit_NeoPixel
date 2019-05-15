
#ifndef ADAFRUIT_HYBRIDNEOPIXEL_H_
#define ADAFRUIT_HYBRIDNEOPIXEL_H_

#include <Adafruit_NeoPixel.h>

#include <Vector.h>

#define MAX_STRIPS 4

class Adafruit_HybridNeoPixel : public Adafruit_NeoPixel {

public:
	Adafruit_HybridNeoPixel(uint8_t p=6);
	~Adafruit_HybridNeoPixel();

	void add(uint16_t n, neoPixelType type=NEO_GRB + NEO_KHZ800);
	void alloc(void);

	void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
	void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b,
			uint8_t w);
	void setPixelColor(uint16_t n, uint32_t c);

	void setBrightness(uint8_t);

private:

	Adafruit_NeoPixel * np_storage_array[MAX_STRIPS];
	Vector<Adafruit_NeoPixel *> _strips;
};


#endif /* ADAFRUIT_HYBRIDNEOPIXEL_H_ */
