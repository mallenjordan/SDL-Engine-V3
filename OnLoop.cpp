#include "Omega.h"

void appOmega::OnLoop() {

	ObjectPlayer->changeVelocityY(1);
	ObjectPool.updateAllObjects();
	
	// Recenter the camera to the player object
	displayCamera.updateCameraTarget(ObjectPlayer->boundRect.x, ObjectPlayer->boundRect.y);
}
