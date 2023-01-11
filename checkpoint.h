#include <raylib.h>
#include <cmath>
#include <vector>
#include <iostream>

class Tracker {
    public:
        Tracker(int newRayAmount = 8, int newRaylenght = 125);
        ~Tracker();
        void update(float *x, float *y, double newAngle, GameMapE* map);
        void draw();
        double lerp(double A, double B, double t);
        Vector4 getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D);
        void SetSpawn(Vector2* ps);
        int rayAmountInt;
        std::vector<Vector3> hitCoordVec3; 
    private:
        bool calcRayHits(int endRayLoc, GameMapE* map);
        void castRays();

        Vector2 startRay;
        Vector3 hitCoordVec;
        std::vector<Vector2> eindRay, wallVector, outerWallvector; 

        int mapArraySize, outerMapArraySize, rayAmount;
        double angle, rayLenght, rayAngle;
        const double raySpread = M_PI*2;
        const double halfRaySpread = raySpread/2;

};

Tracker::Tracker(int newRayAmount, int newRaylenght) {
    rayAmount = newRayAmount;
    rayAmountInt = newRayAmount;
    rayLenght = newRaylenght;
}

Tracker::~Tracker() {

}

double Tracker::lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

Vector4 Tracker::getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
    double tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
    double uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
    double bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);
    double retVal[3];
    Vector4 test;
    test.x = 0;
    test.y = 0;
    test.z = 0;
    test.w = 0;
    if (bottom != 0) {
        double t = tTop/bottom;
        double u = uTop/bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            test.x = lerp(A.x, B.x, t);
            test.y = lerp(A.y, B.y, t);
            test.z = t;
            test.w = 5;
            return test;
        }
    }
    return test;
}



bool Tracker::calcRayHits(int endRayLoc, GameMapE* map) {
    std::vector<Vector3> touches;
    Vector2 endRay = eindRay.at(endRayLoc);

    for (int i=0; i < map->bestRoute.size(); i++) {
        Vector4 test;
        if (i < map->bestRoute.size()-1) {
            test = getIntersection(startRay, endRay, map->bestRoute.at(i), map->bestRoute.at(i+1));
        } else {
            test = getIntersection(startRay, endRay, map->bestRoute.at(i), map->bestRoute.at(0));
        }

        if (test.w == 5) {
            Vector3 valueVec;
            valueVec.x = test.x;
            valueVec.y = test.y;
            valueVec.z = test.z;
            touches.push_back(valueVec); 
        }

    }

    if (touches.size() > 0) {
        double minOffset = touches.at(0).z;
        int minOffsetLocation = 0;
        for (int i=0; i < touches.size(); i++) {
            if (minOffset > touches.at(i).z) {
                minOffset = touches.at(i).z;
                minOffsetLocation = i;
            }

        }
        hitCoordVec = touches.at(minOffsetLocation);
        return true;
    }

    return false;
}

void Tracker::draw() {
    int closest = 0;
    double closestDistance = sqrt(pow(hitCoordVec3.at(0).x - startRay.x, 2) + pow(hitCoordVec3.at(0).y - startRay.y, 2));
    for (int i=0; i < hitCoordVec3.size(); i++) {
        double distance = sqrt(pow(hitCoordVec3.at(i).x - startRay.x, 2) + pow(hitCoordVec3.at(i).y - startRay.y, 2));
        if (distance < closestDistance) {
            closest = i;
            closestDistance = distance;
        }
    }
    DrawLineV(startRay, {hitCoordVec3.at(closest).x, hitCoordVec3.at(closest).y}, RED);
}

void Tracker::update(float* x, float* y, double newAngle, GameMapE* map) {
    eindRay = {};
    hitCoordVec3 = {};
    angle = newAngle;

    startRay.x = *x;
    startRay.y = *y;

    castRays();
    for (int i=0; i < rayAmount; i++) {
        if (calcRayHits(i, map)) {
            hitCoordVec3.push_back(hitCoordVec);
        } else {
            hitCoordVec3.push_back({});
        }
        for (int i=0; i < 8; i++) {
            
        }
    }
}

void Tracker::castRays() {
    for (int i=0; i < rayAmount; i++) {
        double value;
        if (i != 0) {
            value = i/float(rayAmount);
        } else {
            value = 0;
        }

        double rayAngle = lerp(halfRaySpread, -halfRaySpread, value);
        rayAngle += angle;

        float eindx = (startRay.x - sin(rayAngle) * rayLenght);
        float eindy = (startRay.y - cos(rayAngle) * rayLenght);

        Vector2 newEindRay = {eindx, eindy};

        eindRay.push_back(newEindRay);
    }
}
