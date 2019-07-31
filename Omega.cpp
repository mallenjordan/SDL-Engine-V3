#include "Omega.h"

#undef main

void fSDLPrintError(char* strMessage) {
	printf("%s Error : %s\n", strMessage, SDL_GetError());
}

appOmega::appOmega() {
    bRunning = true;
	windowFlags = 0;
}

void appOmega::fToggleFullscreen() {
	Uint32 flags = (SDL_GetWindowFlags(displayWindow) ^ SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (SDL_SetWindowFullscreen(displayWindow, flags) < 0) {
		std::cout << "Toggling fullscreen mode failed: " << SDL_GetError() << std::endl;
	}
	if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
		displayCamera.bFullscreen = true;
		SDL_DisplayMode currentDisplay;
		SDL_GetCurrentDisplayMode(0, &currentDisplay);

		displayCamera.dstRect = { 0, 0, currentDisplay.w, currentDisplay.h };
		displayCamera.srcRect = { 0, 0, currentDisplay.w, currentDisplay.h };
	}
	else {
		displayCamera.bFullscreen = false;
		displayCamera.dstRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		displayCamera.srcRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	}
}

int appOmega::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(bRunning) {
		systemTimer.getTick();

        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();

        OnRender();

		systemTimer.setDelay();
    }

    OnCleanup();

    return 0;
}

int main(int argc, char* argv[]) {
    appOmega theApp;

    return theApp.OnExecute();
}
