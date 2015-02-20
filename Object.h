#define SCREENWIDTH 1024
#define SCREENHEIGHT 768
#include "Hitbox.h"
using namespace sf;
using namespace std;

class Object {
private:
    Texture O_Texture;
    int ID;
public:
    int getID() {
        return ID;
    }
    Texture getTexture() {
        return O_Texture;
    }
    float mass;
    Sprite O_Sprite;
    Vector2f size;
    Vector2f position;
    Vector2f acceleration;
    Vector2f velocity;
    Hitbox* hitbox;
    Object() : ID(-1), position(Vector2f(0,0)) {}
	//NullObject to return when GetObjectFromID fails.
	//Max amount of objects allowed on screen
	static Object ActiveObjects[10];
	//Returns a pointer to an Object class from its ID
	static Object * GetObjectFromID(int IDQuery);
	static int CreateNewObject(Texture Texture, Vector2f Position, hType Hitbox);

    bool RemoveObject();
	static void PhysicsUpdate();
};
