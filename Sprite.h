
class cTexture {
public:
	cTexture();
	~cTexture();

	bool loadFromFile(SDL_Renderer* gRenderer, std::string strFilename);

	void freeTexture();

	void setColor(Uint8 ui8Red, Uint8 ui8Green, Uint8 ui8Blue);

	void setBlendMode(SDL_BlendMode bmBlending);

	void setAlpha(Uint8 ui8Alpha);

	void fRenderTexture(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

	SDL_Texture* pTexture;

	int vWidth;
	int vHeight;
};