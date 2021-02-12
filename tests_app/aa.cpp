#include <stdint.h>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <math.h>

static int counter = -1;

struct CRGB {
    uint8_t clr;
    
    CRGB() {
		clr = 0;
    }
	
	CRGB(uint8_t clr) : clr(clr) {
    }
	
	inline CRGB& operator+= (const CRGB& rhs )
    {
		unsigned int t = clr + rhs.clr;
		if( t > 255) t = 255;
		clr = t;
        return *this;
    }
};

static constexpr int LEDS_WIDTH = 15;
static constexpr int LEDS_HEIGHT = 12;
static constexpr int NUM_LEDS = LEDS_HEIGHT * LEDS_WIDTH;

static CRGB leds[NUM_LEDS];

static uint8_t getPixelIndex(uint8_t x, uint8_t y) {
	return x + y * LEDS_WIDTH;
}

static void drawPixelInternAA(float ix, float iy, const CRGB &color) {
	if (ix > LEDS_WIDTH - 1 || iy > LEDS_HEIGHT - 1) {
		printf("Failed to print pixel at x=%f y=%f\n", ix, iy);
		return;
	}

	for (int x = floor(ix); x <= ceil(ix); ++x) {
		for (int y = floor(iy); y <= ceil(iy); ++y) {
			float px = 1 - abs(ix - x);
			float py = 1 - abs(iy - y);
			float pp = px * py;
			int ledIndex = getPixelIndex(x, y);
			CRGB ledColor(color.clr * pp);
			leds[ledIndex] += ledColor;
		}
	}
}


void printAll() {
    for(int i = 0; i < NUM_LEDS; ++i) {
        CRGB &led = leds[i];
        if (i != 0 && i % LEDS_WIDTH == 0) {
            printf("\n");        
        }
        printf("%*d ", 3, led.clr);
    }
    printf("\n");   
}

int main(int argc, const char** argv) {
    printf("Before anything\n");
    printAll();
    printf("Starting to move image\n");
	float dx = 0.2;
	float dy = 0.2;
	float x = 0;
	float y = 0;
    for (int i = 0; i < 10; ++i) {
		memset(leds, 0, sizeof(leds));
		drawPixelInternAA(x, y, CRGB(100));
		x += dx;
		y += dy;
		printf("Step %d.\n", i);
		printAll();
	}
	
    printf("Image is moved.\n");
    return 0;
}
