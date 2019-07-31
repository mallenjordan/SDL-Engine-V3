#include "Omega.h"

bool appOmega::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	displayWindow = SDL_CreateWindow("Platformer", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (displayWindow == NULL) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return false;
	}

	displayRenderer = SDL_CreateRenderer(displayWindow, -1, SDL_RENDERER_ACCELERATED);
	if (displayRenderer == NULL) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return false;
	}

	cObject oFloor;
	oFloor.setBoundRect(1, WORLD_PIXELS_HIGH - 200, WORLD_PIXELS_WIDE, 40);
	oFloor.bCanMove = false;
	oFloor.refIndex = OBJECT_FLOOR;
	oFloor.setColor(0, 100, 50, 255);
	ObjectPool.addObject(&oFloor);

	cObject oPlayer;
	oPlayer.setBoundRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 20, 20);
	oPlayer.bCanMove = true;
	oPlayer.refIndex = OBJECT_PLAYER;
	oPlayer.setColor(255, 255, 255, 255);
	oPlayer.velY += 1;
	ObjectPool.addObject(&oPlayer);


	ObjectPlayer = ObjectPool.getObjectRefIndex(OBJECT_PLAYER);

	displayCamera.setupTexture(displayRenderer);
	// update to player object
	displayCamera.updateCameraTarget(ObjectPlayer->boundRect.x, ObjectPlayer->boundRect.y);

    return true;
}
