#include "Omega.h"

cObject::cObject() {
	velX = 0.0;
	velY = 0.0;
	bGrounded = false;
}

cObject::~cObject() {

}

void cObject::setColor(Uint8 pRed, Uint8 pGreen, Uint8 pBlue, Uint8 pAlpha) {
	cRed = pRed;
	cGreen = pGreen;
	cBlue = pBlue;
	cAlpha = pAlpha;
}

void cObject::setBoundRect(int iX, int iY, int iW, int iH) {
	boundRect.x = iX;
	boundRect.y = iY;
	boundRect.w = iW;
	boundRect.h = iH;
}

void cObject::renderObject(SDL_Renderer *pRenderer) {
	SDL_SetRenderDrawColor(pRenderer, cRed, cGreen, cBlue, cAlpha);
	SDL_RenderFillRect(pRenderer, &boundRect);
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
}

void cObject::changeVelocityX(double nVelX) {
	velX += nVelX;
	// Set govenor on the velocity.
	if (abs(velX) >= (double)GLOBAL_PHYSICS_MAX_VELOCITY) { velX = (double)getPolarity((int)velX) * (double)GLOBAL_PHYSICS_MAX_VELOCITY;  }
}

void cObject::changeVelocityY(double nVelY) {
	velY += nVelY;
	if (velY < 0) { bGrounded = false;  }
	// Set govenor on the velocity.
	if (abs(velY) >= (double)GLOBAL_PHYSICS_MAX_VELOCITY) { velY = (double)getPolarity((int)velY) * (double)GLOBAL_PHYSICS_MAX_VELOCITY; }
}

void cObject::checkBoundRect() {
	if (boundRect.x < 0) { boundRect.x = 0; }
	if (boundRect.y < 0) { boundRect.y = 0; }
	if (boundRect.x + boundRect.w > WORLD_PIXELS_WIDE) { boundRect.x = WORLD_PIXELS_WIDE - boundRect.w; }
	if (boundRect.y + boundRect.h > WORLD_PIXELS_HIGH) { boundRect.y = WORLD_PIXELS_HIGH - boundRect.h; }
}



void cObjectPool::addObject(cObject *pObject) {
	if (pObject != nullptr) { 
		cObject nObject;
		nObject.setColor(pObject->cRed, pObject->cGreen, pObject->cBlue, pObject->cAlpha);
		nObject.setBoundRect(pObject->boundRect.x, pObject->boundRect.y, pObject->boundRect.w, pObject->boundRect.h);
		nObject.bCanMove = pObject->bCanMove;
		nObject.velX = pObject->velX;
		nObject.velY = pObject->velY;
		nObject.refIndex = pObject->refIndex;
		Objects.push_back(nObject);
	}
}

int getPolarity(int velocityQuestion) {
	return ((velocityQuestion > 0) ? 1 : ((velocityQuestion < 0) ? -1 : 0));
}

bool isCollidingY(SDL_Rect *OBJA, SDL_Rect *OBJB) {
	if ((OBJA->y + OBJA->h) < (OBJB->y)) { return false; }
	if ((OBJB->y + OBJB->h) < (OBJA->y)) { return false; }
	return true;
}

bool isCollidingX(SDL_Rect *OBJA, SDL_Rect *OBJB) {
	if ((OBJA->x) > (OBJB->x + OBJB->w)) { return false; }
	if ((OBJB->x) > (OBJA->x + OBJA->w)) { return false; }
	return true;
}

double getPhysicsGravity(double velY) {
	if (velY == 0) { return 0; }
	else { 
		velY += GLOBAL_PHYSICS_GRAVITY;
		if (velY > GLOBAL_PHYSICS_MAX_VELOCITY) { return GLOBAL_PHYSICS_MAX_VELOCITY; }
		else if (velY == 0) { return GLOBAL_PHYSICS_GRAVITY; }
		else { return velY; }
	}
}

double getPhysicsDrag(double velN) {
	// Drag is preasure in the opposite motion
	// Returns the changed state/value of velN

	// Get the polarity of the velocity magnitude
	int iPolarity = ((velN > 0) ? 1 : ((velN < 0) ? -1 : 0));
	if (iPolarity == 0) { return 0; }

	// Reverse the polarity (any number * -1 reverses)
	iPolarity *= -1;

	// Add the drag on the new polarity
	// the GLOBAL_PHYSICS_DRAG later can change for the state of environment and timing
	velN += (GLOBAL_PHYSICS_DRAG * (double)iPolarity);

	// Make sure we did not reverse the motion, wouldn't make sense.
	// Just return zero.
	// if reversePolarity adds and the new value is larger than zero
	// or
	// reversePolarity removes and the new value is less than zero
	// We want full stop on drag. Return zero.
	if (((iPolarity == 1) && (velN > 0)) || ((iPolarity == -1) && (velN < 0))) { return 0; }

	// Put a govenor on the speed of the drag?
	// Probably not because it is scaling down a velocity to zero.
	return velN;
}

void getSuperBoundRect(SDL_Rect *pRect, cObject *pObject) {
	pRect->x = pObject->boundRect.x;
	pRect->y = pObject->boundRect.y;
	pRect->w = pObject->boundRect.w;
	pRect->h = pObject->boundRect.h;

	
	if (pObject->velX > 0) { pRect->w += (int)pObject->velX; }
	else if (pObject->velX < 0) { pRect->x += (int)pObject->velX; }
	// Means zero velocity X Axis, do nothing to shift the super rect.

	if (pObject->velY > 0) { pRect->h += (int)pObject->velY; }
	else if (pObject->velY < 0) { pRect->y += (int)pObject->velY; }
	// Means zero velocity Y Axis, do nothing to shift the super rect.
	
}

void cObjectPool::updateAllObjects() {
	SDL_Rect superBoundRect;
	bool bCollideX, bCollideY;
	int iPolarity = 0;
	int OBJECT_A_INDEX = 0;
	int OBJECT_B_INDEX = 0;
	int OBJECT_COUNT = (int)Objects.size();

	// Loop through each Object in the list
	for (OBJECT_A_INDEX = 0; OBJECT_A_INDEX < OBJECT_COUNT; OBJECT_A_INDEX++) {
		// If the object can't move skip to the next object.
		if (!Objects[OBJECT_A_INDEX].bCanMove) { continue; }

		// Update the physics applied to all moveable objects here.
		// (Gravity on the y axis)
		Objects[OBJECT_A_INDEX].velY = getPhysicsGravity(Objects[OBJECT_A_INDEX].velY);
		// (Drag on the x axis)
		Objects[OBJECT_A_INDEX].velX = getPhysicsDrag(Objects[OBJECT_A_INDEX].velX);

		// Check if velX or velY are zero, if yes next object. This one is at rest.
		if ((Objects[OBJECT_A_INDEX].velX == 0) && (Objects[OBJECT_A_INDEX].velY == 0)) { continue; }

		// Build temp rect movement structure, old xywh growing to new xywh
		getSuperBoundRect(&superBoundRect, &Objects[OBJECT_A_INDEX]);

		// This is commented out, was for testing on boundries of the rectangles
		//std::cout << "testing super rect x" << superBoundRect.x << " y" << superBoundRect.y << " w " << superBoundRect.w << " h" << superBoundRect.h << std::endl;

		// Loop through all other objects (skipping self)
		for (OBJECT_B_INDEX = 0; OBJECT_B_INDEX < OBJECT_COUNT; OBJECT_B_INDEX++) {
			// If we are using the same index for both objects skip to next.
			// Test if it is self.
			if (OBJECT_A_INDEX == OBJECT_B_INDEX) { continue; }

			// Check for the x and y collisions of Change state of ObjectA vs ObjectB
			bCollideX = isCollidingX(&superBoundRect, &Objects[OBJECT_B_INDEX].boundRect);
			bCollideY = isCollidingY(&superBoundRect, &Objects[OBJECT_B_INDEX].boundRect);

			// If there is a collision on either X or Y Axis, Pixel Collision happens here.
			// update back to bCollideX and bCollideY

			// There needs to be a test which Axis was hit first.
			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			// And handle that axis first. Then retest?

			// Was there a collision between the two objects on the X Axis?
			if (bCollideX) {
				if (bCollideY) {
					// Yes, collision happened on the X Axis

					// Get the direction the movement was in
					// getPolarity... (returns -1, 0, 1), need to typecase to int from double.
					iPolarity = getPolarity((int)Objects[OBJECT_A_INDEX].velX);

					// Stop all X Axis Velocity (will update after checks)
					// Makes sense because something was hit by ObjectA so halt movement.
					//Objects[OBJECT_A_INDEX].velX = 0;

					if ((Objects[OBJECT_A_INDEX].velY == 0) && (Objects[OBJECT_A_INDEX].bGrounded)) {
						/*
						Objects[OBJECT_A_INDEX].velX = 0;
						// Correct the ObjectA position to stop right next to the ObjectB using iPolarity direction.
						if (iPolarity == 1) {
							// The polarity is positive, ObjectA is moving right
							// Shift ObjectA one Pixel to the left of ObjectB

							Objects[OBJECT_A_INDEX].boundRect.x = Objects[OBJECT_B_INDEX].boundRect.x - Objects[OBJECT_A_INDEX].boundRect.w - 1;
						}
						else if (iPolarity == -1) {
							// The polarity is negative, ObjectA is moving left
							// Shift ObjectA one Pixel to the right of ObjectB

							Objects[OBJECT_A_INDEX].boundRect.x = Objects[OBJECT_B_INDEX].boundRect.x + Objects[OBJECT_B_INDEX].boundRect.w + 1;
						}
						// There will never be a polarity of zero here.
						*/
					}
				}
			}

			// Was there a collision between the two objects on the Y Axis?
			if (bCollideY) {
				if (bCollideX) {
					// Yes, collision happened on the Y Axis

					// Get the direction the movement was in
					// getPolarity... (returns -1, 0, 1), need to typecase to int from double.
					iPolarity = getPolarity((int)Objects[OBJECT_A_INDEX].velY);

					// Correct the ObjectA position to stop on falling Y Axis to ObjectB.
					if (iPolarity == 1) {
						// The polarity is positive, ObjectA fell onto ObjectB
						// (Here is where the bGrounded state would be added)
						if ((Objects[OBJECT_A_INDEX].boundRect.y + Objects[OBJECT_A_INDEX].boundRect.h) < Objects[OBJECT_B_INDEX].boundRect.y) {

							// Halt the vertical movement.
							Objects[OBJECT_A_INDEX].velY = 0;

							// Shift ObjectA position right above the ObjectB
							Objects[OBJECT_A_INDEX].boundRect.y = Objects[OBJECT_B_INDEX].boundRect.y - Objects[OBJECT_A_INDEX].boundRect.h - 1;

							// And we are grounded now.
							Objects[OBJECT_A_INDEX].bGrounded = true;
							//std::cout << "Grounded to Object #" << OBJECT_B_INDEX << std::endl;
						}
					}
					// iPolarity == -1 means player is jumping or being accelerated up.
					// Let it go, gravity will correct this back down.
					// iPolarity will never be zero because previous logical setps.
				}
			}
		}

		if (Objects[OBJECT_A_INDEX].bGrounded) { Objects[OBJECT_A_INDEX].velX = getPhysicsDrag(Objects[OBJECT_A_INDEX].velX); }

		// Update the x/y coordinates to the velocity changes in velX and velY
		// The two velocity vectors have been changed after collision testings.
		Objects[OBJECT_A_INDEX].boundRect.x += (int)Objects[OBJECT_A_INDEX].velX;
		Objects[OBJECT_A_INDEX].boundRect.y += (int)Objects[OBJECT_A_INDEX].velY;

		Objects[OBJECT_A_INDEX].checkBoundRect();
	}
}

void cObjectPool::renderAllObjects(SDL_Renderer *pRenderer) {
	int INDEX = 0;
	for (INDEX = 0; INDEX < (int)Objects.size(); INDEX++) {
		Objects[INDEX].renderObject(pRenderer);
	}
}

cObject *cObjectPool::getObjectRefIndex(int iRefIndex) {
	int INDEX = 0;
	for (INDEX = 0; INDEX < (int)Objects.size(); INDEX++) {
		if (Objects[INDEX].refIndex == iRefIndex) { return &Objects[INDEX]; }
	}

	return NULL;
}