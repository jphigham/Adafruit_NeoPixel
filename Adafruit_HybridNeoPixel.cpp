
#include "Adafruit_HybridNeoPixel.h"

Adafruit_HybridNeoPixel::Adafruit_HybridNeoPixel(uint8_t p)
: Adafruit_NeoPixel()
{
	setPin(p);
	_strips.setStorage(np_storage_array, MAX_STRIPS, 0);
}

Adafruit_HybridNeoPixel::~Adafruit_HybridNeoPixel()
{
	for (int i=0; i < _strips.size(); i++)
		delete _strips[i];
	_strips.clear();
}

void Adafruit_HybridNeoPixel::add(uint16_t n, neoPixelType type)
{
	Adafruit_NeoPixel *np = new Adafruit_NeoPixel();
	np->setPin(pin);
	np->updateType(type);
	np->numLEDs = n;
	_strips.push_back(np);
#ifdef VERBOSE
	Serial.println("Added strip");
#endif
}

void Adafruit_HybridNeoPixel::alloc()
{
	free(pixels); // Free existing data (if any)
	numBytes = 0;
#ifdef VERBOSE
	Serial.println("Totaling LEDs");
#endif
	for (int i=0; i < _strips.size(); i++) {
		Adafruit_NeoPixel *np = _strips[i];
		np->pixels = (uint8_t *)numBytes;
		numBytes += np->numLEDs * ((np->wOffset ==  np->rOffset) ? 3 : 4);
		numLEDs += np->numLEDs;
	}
	// Allocate new data -- note: ALL PIXELS ARE CLEARED
#ifdef VERBOSE
	Serial.print("Allocating ");
	Serial.print(numBytes, DEC);
	Serial.println(" bytes of memory");
#endif
	if((pixels = (uint8_t *)malloc(numBytes))) {
		memset(pixels, 0, numBytes);
	} else {
		numLEDs = numBytes = 0;
	}
#ifdef VERBOSE
	Serial.print("Calculating ");
	Serial.print(_strips.size(), DEC);
	Serial.println(" pixel buffer pointers");
	Serial.print("0x");
	Serial.println((long)pixels, HEX);
#endif
	for (int i=0; i < _strips.size(); i++) {
		Adafruit_NeoPixel *np = _strips[i];
		np->pixels = pixels + (uint16_t)np->pixels;
#ifdef VERBOSE
		Serial.print("0x");
		Serial.println((long)np->pixels, HEX);
#endif
	}
}

void Adafruit_HybridNeoPixel::setPixelColor(
 uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
	int numLEDs = 0;
	for (int i=0; i < _strips.size(); i++) {
		if (numLEDs <= n && n < numLEDs + _strips[i]->numLEDs) {
			_strips[i]->setPixelColor(n-numLEDs, r, g, b);
			return;
		}
		numLEDs += _strips[i]->numLEDs;
	}
}

void Adafruit_HybridNeoPixel::setPixelColor(
 uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
	int numLEDs = 0;
	for (int i=0; i < _strips.size(); i++) {
		if (numLEDs <= n && n < numLEDs + _strips[i]->numLEDs) {
			_strips[i]->setPixelColor(n-numLEDs, r, g, b, w);
			return;
		}
		numLEDs += _strips[i]->numLEDs;
	}
}

void Adafruit_HybridNeoPixel::setPixelColor(uint16_t n, uint32_t c)
{
	int numLEDs = 0;
	for (int i=0; i < _strips.size(); i++) {
		if (numLEDs <= n && n < numLEDs + _strips[i]->numLEDs) {
			_strips[i]->setPixelColor(n-numLEDs, c);
			return;
		}
		numLEDs += _strips[i]->numLEDs;
	}
}

void Adafruit_HybridNeoPixel::setBrightness(uint8_t b)
{
	for (int i=0; i < _strips.size(); i++)
		_strips[i]->setBrightness(b);
}
