#include "Object.h"
#include "Game.h"
using namespace std;
class CollisionManager {
private:
	static bool scanForPair(int ID1,int ID2);
	static vector<pair<int, int>> collisionList;
public:
	static vector<pair<int, int>> checkCollisions();
	static int resolveCollisions();
};
