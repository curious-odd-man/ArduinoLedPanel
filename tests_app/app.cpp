#include <stdint.h>
#include <algorithm>
#include <cstring>
#include <cstdio>

static int counter = -1;

struct CRGB {
    uint8_t bytes[3];
    
    CRGB() {
        bytes[0] = '+';
        bytes[1] = ++counter;
        bytes[2] = '-';
    }
};

static constexpr int LEDS_WIDTH = 15;
static constexpr int LEDS_HEIGHT = 12;
static constexpr int NUM_LEDS = LEDS_HEIGHT * LEDS_WIDTH;

static CRGB leds[NUM_LEDS];
static constexpr int LINE_SIZE = LEDS_WIDTH * sizeof(CRGB);

void clearLine(uint8_t y) {
    memset(leds + (y * LINE_SIZE), 0, LINE_SIZE);
}

void moveImageDown() {
    CRGB *dst = leds + (LEDS_HEIGHT - 2) * LEDS_WIDTH;
    CRGB *src = dst - LEDS_WIDTH;
    while (dst >= leds) {
        std::reverse_copy(src, dst, dst);
    }
    clearLine(0);
}


void printAll() {
    for(int i = 0; i < NUM_LEDS; ++i) {
        CRGB &led = leds[i];
        if (i != 0 && i % LEDS_WIDTH == 0) {
            printf("\n");        
        }
        printf("0x%02x%02x%02x ", led.bytes[0], led.bytes[1], led.bytes[2]);
    }
    printf("\n");   
}

int main(int argc, const char** argv) {
    printf("Before anything\n");
    printAll();
    printf("Starting to move image\n");
    moveImageDown();
    printf("Image is moved.\n");
    printAll();
    return 0;
}
