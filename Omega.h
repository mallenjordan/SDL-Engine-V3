#ifndef _OMEGA_H_
    #define _OMEGA_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <stdint.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Camera.h"
#include "Objects.h"
#include "Sprite.h"
#include "Timer.h"

void fSDLPrintError(char* strMessage);

class appOmega {
    private:
        bool    bRunning;
		Uint32 windowFlags;

		SDL_Window*		displayWindow;
		SDL_Renderer*	displayRenderer;
		
		cCamera displayCamera;

		cObjectPool ObjectPool;

		cObject *ObjectPlayer;

		cTimer systemTimer;

    public:

        appOmega();

        int OnExecute();

    public:

        bool OnInit();

        void OnEvent(SDL_Event* eventPassed);

        void OnLoop();

        void OnRender();

        void OnCleanup();

		void fToggleFullscreen();
};

#endif
