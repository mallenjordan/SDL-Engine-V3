#include "Omega.h"

cTimer::cTimer() {
	tickCount = 0;
}

void cTimer::getTick() {
	tickCount = SDL_GetTicks();
}

void cTimer::setDelay() {
	tickTest = SDL_GetTicks() - tickCount;
	if (tickTest < GLOBAL_TIME_TICK_PER_FRAME) {
		SDL_Delay(GLOBAL_TIME_TICK_PER_FRAME - tickTest);
	}
}