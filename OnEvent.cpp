#include "Omega.h"

void appOmega::OnEvent(SDL_Event* eventPassed) {
	if (eventPassed->type == SDL_QUIT) {
		bRunning = false;
	}
	if (eventPassed->type == SDL_KEYDOWN) {
		switch (eventPassed->key.keysym.sym) {
			case SDLK_LEFT:
				ObjectPlayer->changeVelocityX(-6);
				break;
			case SDLK_RIGHT:
				ObjectPlayer->changeVelocityX(6);
				break;
			case SDLK_UP:
				if (ObjectPlayer->bGrounded) {
					ObjectPlayer->changeVelocityY(-20);
				}
				break;
			case SDLK_DOWN:
				
				break;
			case SDLK_p:
				fToggleFullscreen();
				break;
		}
	}
	if (eventPassed->type == SDL_MOUSEBUTTONDOWN) {
		switch (eventPassed->button.button) {
			case SDL_BUTTON_LEFT:
				SDL_Rect mouseClickRect = { eventPassed->button.x, eventPassed->button.y , 0, 0 };
				displayCamera.transCameraToWorldCoord(&mouseClickRect);
				cObject newObject;
				newObject.refIndex = OBJECT_BOX;
				newObject.setBoundRect(mouseClickRect.x, mouseClickRect.y, 300, 15);
				newObject.setColor((rand() % 255), (rand() % 255), (rand() % 255), 255);
				newObject.bCanMove = true;
				newObject.velY = GLOBAL_PHYSICS_GRAVITY;
				ObjectPool.addObject(&newObject);

				// The vector array could possibly shift.
				// Need to gather the reference to the player object again.
				ObjectPlayer = ObjectPool.getObjectRefIndex(OBJECT_PLAYER);
				break;
		}
	}
}
