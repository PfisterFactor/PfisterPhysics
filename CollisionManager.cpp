#include "CollisionManager.h"
#include "Game.h"
using namespace sf;
using namespace std;
vector<pair<int, int>> CollisionManager::collisionList(10);
bool CollisionManager::scanForPair(int ID1,int ID2) {
	for (pair<int, int> p : collisionList) {
		if (((p.first == ID1 && p.second == ID2) || (p.first == ID2 && p.second == ID1))) {
			return true;
		}
	}
	return false;
}
vector<pair<int,int>> CollisionManager::checkCollisions() {
    //Cycles through every shape on screen and returns a list of all collisions in frame
	for (int baseID = 0; baseID < 10; baseID++) {
		Object* basePointer = &Object::ActiveObjects[baseID]; //Pointer to Object::ActiveObjects[baseID] for convinence
		if (basePointer->ID != -1) {
			for (int secondID = 0; secondID < 10; secondID++) {
				if (secondID != baseID) {
					Object* secondPointer = &Object::ActiveObjects[secondID]; //Pointer to Object::ActiveObjects[secondID] for convinence
					if (secondPointer->ID != -1) {
						if (basePointer->hitbox->intersects(secondPointer->hitbox).first) {
							if (!scanForPair(basePointer->ID, secondPointer->ID)) {
								cout << "smoke weeeed errvydaay";
								collisionList.push_back(pair<int, int>(basePointer->ID, secondPointer->ID));
							}
						}
					}
				}
			}
		}
	}
    
	return collisionList;
}
int CollisionManager::resolveCollisions() {
	if (collisionList.empty()) {
		return -2;
	}
	else {
		for (pair<int, int> collision : collisionList) {
			Object* object1 = &Object::ActiveObjects[collision.first]; //Pointer to Object::ActiveObjects[collision.first] for convinence
			Object* object2 = &Object::ActiveObjects[collision.second]; //Pointer to Object::ActiveObjects[collision.second] for convinence
			//Implementation of elastic collision below.
            float newVelocityX1 = (object1->velocity.x * (object1->mass - object2->mass) + (2 * object2->mass * object2->velocity.x)) / (object1->mass + object2->mass);
            float newVelocityY1 = (object1->velocity.y * (object1->mass - object2->mass) + (2 * object2->mass * object2->velocity.y)) / (object1->mass + object2->mass);
            float newVelocityX2 = (object2->velocity.x * (object2->mass - object1->mass) + (2 * object1->mass * object1->velocity.x)) / (object2->mass + object1->mass);
            float newVelocityY2 = (object2->velocity.y * (object2->mass - object1->mass) + (2 * object1->mass * object1->velocity.y)) / (object2->mass + object1->mass);
            //Sets position + velocity so shapes dont get stuck
            object1->position += Vector2f(newVelocityX1,newVelocityX2);
            object2->position += Vector2f(newVelocityX2,newVelocityY2);
            
            object1->velocity = Vector2f(newVelocityX1,newVelocityY1);
            object2->velocity = Vector2f(newVelocityX2,newVelocityY2);
		}
		collisionList.clear();
		return -1;
	}
}