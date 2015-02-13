#include <math.h>
#include "Game.h"
#define PI 3.14159
using namespace std;
using namespace sf;
enum hType {Circular,Polygon,Uninitialized};
class Hitbox {
protected:
    hType type;
public:
    static double getLength(Vector2f a, Vector2f b) {
        double returnLength = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
        return returnLength;
    }
    static double getLength(Vector2f a, Vector2f b, bool unSquared) {
        double returnLength;
        if (unSquared) {
            returnLength = pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
        }
        else {
            returnLength = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
          
        }
        return returnLength;
    }
    hType getType() {
        return type;
    }
    Vector2f position;
	virtual bool contains(Vector2f) = 0;
	virtual  pair<bool, Vector2f> intersects(Hitbox*) = 0;
	virtual Vector2f rotate(int) = 0;
};

class Circle: public Hitbox {
private:
	FloatRect boundingBox;
	inline void updateBounds() {
		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.height = radius;
		boundingBox.width = radius;
	}
    //Bitwise wizardry, thank you Stack Overflow
    size_t highestOneBitPosition(Uint64 a) {
        size_t bits=0;
        while (a!=0) {
            ++bits;
            a>>=1;
        };
        return bits;
    }
    bool exponent_is_safe(Uint64 a, Uint64 b) {
        size_t a_bits=highestOneBitPosition(a);
        return (a_bits*b<=32);
    }
    //End of Bitwise wizardry
    
    long double radiusSquared; //Radius squared for faster calculation of contains and instersects
public:
	FloatRect getBoundBox() {
		return boundingBox;
	}
    Vector2f center; // Center of circle
    long double radius; // Radius of circle
	Circle() : center(Vector2f(-1, -1)), radius(0) { type = Uninitialized; } // Default constructor, assigns center to out of bounds and radius to 0
    
    Circle(Vector2f _position, float _radius) {
		type = Circular;
        radius = _radius;
        position = _position;
        center = Vector2f(position.x + radius, position.y + radius);
        if (exponent_is_safe(radius,2)) {
            radiusSquared = pow(radius,2);
        }
        else {
            throw std::out_of_range("Radius too high! Can't square without overflow!");
        }
        
    }
	
    Vector2f rotate(int degrees) {
        center = Vector2f(position.x + radius, position.y + radius);
        return Vector2f(-1,-1);
    }
     bool contains(Vector2f point) {
        center = Vector2f(position.x + radius, position.y + radius);
		updateBounds();
		if (boundingBox.contains(point)) {
			long double distance = getLength(center, point,true);// Distance formula between points. (x2 - x1)^2 + (y2 - y1)^2

			if (distance <= radiusSquared) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
    }
	 pair<bool, Vector2f> intersects(Hitbox *intersectee) {
		 center = Vector2f(position.x + radius, position.y + radius);
		 updateBounds();
		 if (intersectee->getType() == Circular) {
			 Circle* intersecteeCircle = dynamic_cast<Circle*>(intersectee); //Downcast a hitbox as a circle.
			 if (boundingBox.intersects(intersecteeCircle->getBoundBox())) {

				 intersecteeCircle->center = Vector2f(intersecteeCircle->position.x + intersecteeCircle->radius, intersecteeCircle->position.y + intersecteeCircle->radius);
				 long double distanceBetweenCenters = getLength(center,intersecteeCircle->center,true); // Distance formula between points. (x2 - x1)^2 + (y2 - y1)^2
				 //cout << "-" << distanceBetweenCenters;
				 //cout << "-" << radiusSquared*2 << "-";
				 if (distanceBetweenCenters <= radiusSquared) {
					 Vector2f returnVector = Vector2f(((center.x * intersecteeCircle->radius) + (intersecteeCircle->center.x * radius))
						 / (radius + intersecteeCircle->radius), ((center.y * intersecteeCircle->radius) + (intersecteeCircle->center.y * radius))
						 / (radius + intersecteeCircle->radius)); //Mumbo jumbo calculates the point of collision
					 return pair<bool, Vector2f>(true, returnVector);
				 }
				 else {

					 return pair<bool, Vector2f>(false, Vector2f(0, 0));
				 }

			 }
			 else if (intersectee->getType() == Polygon) {
				 return pair<bool, Vector2f>(false, Vector2f(0, 0)); // Temporary until I figure out how to implement S.A.T
			 }
			 else return pair<bool, Vector2f>(false, Vector2f(0, 0));
		 }
		 else {
			 return pair<bool, Vector2f>(false, Vector2f(0, 0));
		 }
	 }
	 
};