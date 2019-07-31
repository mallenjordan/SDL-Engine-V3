const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WORLD_PIXELS_WIDE = SCREEN_WIDTH * 3;
const int WORLD_PIXELS_HIGH = SCREEN_HEIGHT * 3;

class cCamera {
public:
	cCamera();

	bool bFullscreen;

	SDL_Rect srcRect;
	SDL_Rect dstRect;

	void setupTexture(SDL_Renderer *pRenderer);

	void updateCameraTarget(int targetX, int targetY);

	void transCameraToWorldCoord(SDL_Rect *pRect);

	SDL_Texture *cameraTexture;

	void renderCamera(SDL_Renderer *pRenderer);
};