#include "ColorProgram.h"

typedef std::function<ColorProgram* ()> ProgSupplier;

static const ProgSupplier suppliers[] = { []() {
	return new StaticColorProgram();
},
[]() {
	return new RandomColorProgram();
},
[]() {
	return new LerpColorProgram();
} };

constexpr int NUM_PROGRAMS = sizeof(suppliers) / sizeof(ProgSupplier);

ColorProgram* createRandomColorProgram() {
	return suppliers[random(NUM_PROGRAMS)]();
}

