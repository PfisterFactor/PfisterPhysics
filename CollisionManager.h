#include "Object.h"
#include "Game.h"
using namespace std;
class CollisionManager {
private:
	static bool scanForPair(int ID1,int ID2);
	static vector<pair<int, int>> objectCollisionList;
    static vector<pair<Object,int>> wallCollisionList;
public:
	static vector<pair<int, int>> checkObjectCollisions();
	static int resolveObjectCollisions();
    static vector<pair<Object,int>> checkWallCollisions();
    static int resolveWallCollisions();
};
