#include "Omega.h"

cTexture::cTexture() {
	pTexture = NULL;
	vWidth = 0;
	vHeight = 0;
}

cTexture::~cTexture() {
	freeTexture();
}

bool cTexture::loadFromFile(SDL_Renderer *gRenderer, std::string path) {
	freeTexture();

	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) { fSDLPrintError("IMG_load"); return false; }
	else {
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) { fSDLPrintError("SDL_CreateTextureFromSurface"); return false; }
		else {
			//Get image dimensions
			vWidth = loadedSurface->w;
			vHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	pTexture = newTexture;
	return pTexture != NULL;
}

void cTexture::freeTexture() {
	if (pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
		vWidth = 0;
		vHeight = 0;
	}
}

void cTexture::setColor(Uint8 ui8Red, Uint8 ui8Green, Uint8 ui8Blue) {
	SDL_SetTextureColorMod(pTexture, ui8Red, ui8Green, ui8Blue);
}

void cTexture::setBlendMode(SDL_BlendMode bmBlending) {
	SDL_SetTextureBlendMode(pTexture, bmBlending);
}

void cTexture::setAlpha(Uint8 ui8Alpha) {
	SDL_SetTextureAlphaMod(pTexture, ui8Alpha);
}

void cTexture::fRenderTexture(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, vWidth, vHeight };

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, pTexture, clip, &renderQuad, angle, center, flip);
}

int cTexture::getWidth() {
	return vWidth;
}

int cTexture::getHeight() {
	return vHeight;
}