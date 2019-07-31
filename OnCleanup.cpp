#include "Omega.h"

void appOmega::OnCleanup() {

	SDL_DestroyRenderer(displayRenderer);
	SDL_DestroyWindow(displayWindow);

	SDL_Quit();
}
