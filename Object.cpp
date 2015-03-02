#include "Object.h"
#include "Game.h"
using namespace sf;
using namespace std;
vector<Object> Object::ActiveObjects = vector<Object>(10);
 Object* Object::GetObjectFromID(int IDQuery) {
	for (int index = 0; index < 10; index++) {
		if (ActiveObjects[index].ID == IDQuery) {
			return &ActiveObjects[index];
			cout << "\nIt's a match!";
		}
	}
	return NULL;
}
int Object::CreateNewObject(Texture Texture, Vector2f Position, hType Hitbox) {
	 for (int index = 0; 0 < 10; index++) {
		 if (ActiveObjects[index].getID() == -1) {
			 Object * NewObject = &ActiveObjects[index];
			 NewObject->mass = 10;
			 NewObject->ID = index;
			 NewObject->position = Position;
			 NewObject->O_Texture = Texture;
			 NewObject->size = Texture.getSize();
			 NewObject->O_Sprite.setTexture(ActiveObjects[index].O_Texture);
             switch (Hitbox) {
                 case Circular:
                     if (Texture.getSize().x == Texture.getSize().y) {
                         NewObject->hitbox = new Circle(Vector2f(0,0),Texture.getSize().x);
                     }
                     else {
                         throw invalid_argument("Size isn't valid for circle shape");
                     }
                     break;
                     
                 case Polygon:
                     throw invalid_argument("Unsupported");
                     break;
                 default:
                     throw invalid_argument("Unsupported");
                     break;
             }
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