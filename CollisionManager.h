#include "Object.h"
#include "Game.h"
using namespace std;
class CollisionManager {
private:
	static bool scanForPair(int ID1,int ID2);
	static vector<pair<int, int>> objectCollisionList;
    static vector<pair<int,int>> wallCollisionList;
	static void checkObjectCollisions();
	static void checkWallCollisions();
public:
	static int resolveObjectCollisions();
    static int resolveWallCollisions();
};
