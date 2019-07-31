#include "Omega.h"

void appOmega::OnRender() {
	// DO NOT CHANGE---------------------------------------------------
	// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

	// target the camera texture for rendering
	SDL_SetRenderTarget(displayRenderer, displayCamera.cameraTexture);
	// clear the camera texture
	SDL_RenderClear(displayRenderer);
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// DO NOT CHANGE---------------------------------------------------



	// Here render all to the displayRenderer
	// It will cast to the movable camera view port
	ObjectPool.renderAllObjects(displayRenderer);

	ObjectPlayer->renderObject(displayRenderer);

	// DO NOT CHANGE---------------------------------------------------
	// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	// set the renderer target back to the default
	SDL_SetRenderTarget(displayRenderer, NULL);
	
	SDL_RenderClear(displayRenderer);

	// now render the camera texture to the render default
	displayCamera.renderCamera(displayRenderer);

	// here display any overhead menu or hud to the display render default (overhead all in aspect)

	// push the final renderer to the screen
	SDL_RenderPresent(displayRenderer);
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// DO NOT CHANGE---------------------------------------------------
}
