#include <string>
#include <vector>

#define OBJECT_PLAYER 0
#define OBJECT_BOX 1
#define OBJECT_FLOOR 2

#define GLOBAL_PHYSICS_GRAVITY 0.2
#define GLOBAL_PHYSICS_DRAG 0.2
#define GLOBAL_PHYSICS_MAX_VELOCITY 20

int getPolarity(int velocityQuestion);

bool isCollidingY(SDL_Rect *OBJA, SDL_Rect *OBJB);
bool isCollidingX(SDL_Rect *OBJA, SDL_Rect *OBJB);

double getPhysicsGravity(double velY);
double getPhysicsDrag(double velN);

class cObject {
	public:
		cObject();
		~cObject();

		int refIndex;
		bool bCanMove;
		bool bGrounded;

		SDL_Rect boundRect;

		double velX;
		double velY;

		Uint8 cRed;
		Uint8 cGreen;
		Uint8 cBlue;
		Uint8 cAlpha;

		void setColor(Uint8 pRed, Uint8 pGreen, Uint8 pBlue, Uint8 pAlpha);
		void setBoundRect(int iX, int iY, int iW, int iH);
		void renderObject(SDL_Renderer *pRenderer);

		void changeVelocityX(double nVelX);
		void changeVelocityY(double nVelY);

		void checkBoundRect();
	private:
};

class cObjectPool {
	public:
		std::vector <cObject> Objects;

		void addObject(cObject *pObject);

		void updateAllObjects();

		void renderAllObjects(SDL_Renderer *pRenderer);

		cObject *getObjectRefIndex(int iRefIndex);
};

void getSuperBoundRect(SDL_Rect *pRect, cObject *pObject);
