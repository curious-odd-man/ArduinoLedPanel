#include "../svc/LedService.h"
#include "../util/Settings.h"
#include "../prog/Effects.h"

LedService::LedService() : imageProgram(nullptr) {

}

LedService::~LedService() {
    deleteProgram();
}

void LedService::deleteProgram() {
    if (imageProgram != nullptr) {
        delete imageProgram;
        imageProgram = nullptr;
    }
}

void LedService::begin() {
    Leds::initialize();
    imageProgram = new TimeProgram();
}

void LedService::loop() {
    if (imageProgram != nullptr) {
        imageProgram->loop();
    }
}

void LedService::drawPixel(uint8_t x, uint8_t y, CRGB &color) {
    Leds::drawPixel(x, y, color);
}

void LedService::startNewProgram(LightProgram *program) {
    deleteProgram();
    imageProgram = program;
}
