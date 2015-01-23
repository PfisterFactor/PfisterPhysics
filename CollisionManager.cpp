#include "CollisionManager.h"
#include "Game.h"
#define SCREENWIDTH 1024
#define SCREENHEIGHT 768
using namespace sf;
using namespace std;
enum wallSides {Left,Top,Right,Bottom};
vector<pair<int, int>> CollisionManager::objectCollisionList(10);
vector<pair<int,int>> CollisionManager::wallCollisionList(40);
bool CollisionManager::scanForPair(int ID1,int ID2) {
	for (pair<int, int> p : objectCollisionList) {
		if (((p.first == ID1 && p.second == ID2) || (p.first == ID2 && p.second == ID1))) {
			return true;
		}
	}
	return false;
}
vector<pair<int,int>> CollisionManager::checkObjectCollisions() {
    //Cycles through every shape on screen and returns a list of all collisions in frame
	for (int baseID = 0; baseID < 10; baseID++) {
		Object* basePointer = &Object::ActiveObjects[baseID]; //Pointer to Object::ActiveObjects[baseID] for convinence
		if (basePointer->getID() != -1) {
			for (int secondID = 0; secondID < 10; secondID++) {
				if (secondID != baseID) {
					Object* secondPointer = &Object::ActiveObjects[secondID]; //Pointer to Object::ActiveObjects[secondID] for convinence
					if (secondPointer->getID() != -1) {
						if (basePointer->hitbox->intersects(secondPointer->hitbox).first) {
							if (!scanForPair(basePointer->getID(), secondPointer->getID())) {
								cout << "Collision!\n";
								objectCollisionList.push_back(pair<int, int>(basePointer->getID(), secondPointer->getID()));
							}
						}
					}
				}
			}
		}
	}
    
	return objectCollisionList;
}
int CollisionManager::resolveObjectCollisions() {
	if (objectCollisionList.empty()) {
		return 1;
	}
	else {
		for (pair<int, int> collision : objectCollisionList) {
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
		objectCollisionList.clear();
		return 0;
	}
}
vector<pair<int,int>> CollisionManager::checkWallCollisions() {
    for (int baseID = 0; baseID < 10; baseID++) {
        Object* basePointer = &Object::ActiveObjects[baseID]; //Pointer to Object::ActiveObjects[baseID] for convinence
        if (basePointer->position.x + basePointer->getTexture().getSize().x > SCREENWIDTH) {
            wallCollisionList.push_back(pair<int,int>(basePointer->getID(),Right));
        }
        if (basePointer->position.x < 0) {
            wallCollisionList.push_back(pair<int,int>(basePointer->getID(),Left));
        }
        if (basePointer->position.y + basePointer->getTexture().getSize().y > SCREENHEIGHT) {
            wallCollisionList.push_back(pair<int,int>(basePointer->getID(),Bottom));
        }
        if (basePointer->position.y  < 0) {
            wallCollisionList.push_back(pair<int,int>(basePointer->getID(),Top));
        }
        
    }
    return wallCollisionList;
}
int CollisionManager::resolveWallCollisions() {
    if (wallCollisionList.empty()) {
        return 1;
    }
    for (pair<int,int> pair : wallCollisionList) {
        Object* basePointer = &Object::ActiveObjects[pair.first];
        if (pair.second == Left || pair.second == Right) {
            basePointer->velocity.x = -basePointer->velocity.x;
        }
        if (pair.second == Top || pair.second == Bottom) {
            basePointer->velocity.y = -basePointer->velocity.y;
        }
    }
    wallCollisionList.clear();
    return 0;
}
