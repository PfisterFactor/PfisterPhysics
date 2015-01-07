#include "Object.h"
#include "Game.h"
using namespace sf;
using namespace std;
 Object* Object::GetObjectFromID(int IDQuery) {
	for (int index = 0; index < 10; index++) {
		if (ActiveObjects[index].ID == IDQuery) {
			return &ActiveObjects[index];
			cout << "\nIt's a match!";
		}
	}
	return NULL;
}
int Object::CreateNewObject(Texture Texture, Vector2f Position, Hitbox* Hitbox) {
	 for (int index = 0; 0 < 10; index++) {
		 if (ActiveObjects[index].ID == -1) {
			 Object * NewObject = &ActiveObjects[index];
			 NewObject->mass = 10;
			 NewObject->ID = index;
			 NewObject->position = Position;
			 NewObject->O_Texture = Texture;
			 NewObject->O_Sprite.setTexture(ActiveObjects[index].O_Texture);
			 NewObject->hitbox = Hitbox;
			 cout << "\nInstantiating new object with ID of " << index << " at pixel coordinates (" << Position.x << "," << Position.y << ")";
			 return index;
		 }
	 }
	 cout << "\nCouldn't create object, scene most likely full";
	 return -1;
}
bool Object::RemoveObject()  {
    if (this->ID == -1) {
        return false;
    }
    else {
        this->velocity = Vector2f();
        this->acceleration = Vector2f();
        this->mass = 0;
        this->ID = -1;
        this->O_Sprite = Sprite();
        this->O_Texture = Texture();
        delete this->hitbox;
        return true;
    }
}