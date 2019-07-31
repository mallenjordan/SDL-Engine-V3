#include "Omega.h"

cCamera::cCamera() {
	bFullscreen = false;
	srcRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	dstRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

void cCamera::setupTexture(SDL_Renderer *pRenderer) {
	cameraTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WORLD_PIXELS_WIDE, WORLD_PIXELS_HIGH);
}

void cCamera::updateCameraTarget(int targetX, int targetY) {
	srcRect.x = targetX - srcRect.w / 2;
	srcRect.y = targetY - srcRect.h / 2;
	if (srcRect.x < 0) { srcRect.x = 0; }
	if (srcRect.x > WORLD_PIXELS_WIDE - srcRect.w) { srcRect.x = WORLD_PIXELS_WIDE - srcRect.w; }

	if (srcRect.y < 0) { srcRect.y = 0; }
	if (srcRect.y > WORLD_PIXELS_HIGH - srcRect.h) { srcRect.y = WORLD_PIXELS_HIGH - srcRect.h; }
}

void cCamera::transCameraToWorldCoord(SDL_Rect *pRect) {
	pRect->x += srcRect.x;
	pRect->y += srcRect.y;
}

void cCamera::renderCamera(SDL_Renderer *pRenderer) {
	SDL_RenderCopy(pRenderer, cameraTexture, &srcRect, &dstRect);
}