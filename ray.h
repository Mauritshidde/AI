#include <raylib.h>
#include <cmath>
#include <vector>
#include <iostream>

// #include "GameMap.h"
// #include "utils.h"

// GameMapE map2;




class Rays {
    public:
        Rays();
        ~Rays();
        void update(Vector2 newStart, double newAngle);
        void draw();
        // std::vector<Vector2> returnMap() { GameMapE map; return map.wallVectorVec;};
        double lerp(double A, double B, double t);
        Vector4 getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D);
        void setWallVec(std::vector<Vector2> vec, int arraySize, std::vector<Vector2> outervec, int outerArraySize) {wallVector = vec; mapArraySize = arraySize; outerWallvector = outervec; outerMapArraySize=outerArraySize;};
    private:
        bool calcRayHits(int endRayLoc);
        void castRays();

        std::vector<Vector2> eindRay, wallVector, outerWallvector; 
        std::vector<Vector3> hitCoordVec3; 
        Vector2 startRay;
        Vector3 hitCoordVec;
        
        double rayAmount, angle, rayLenght, rayAngle;
        const double raySpread = M_PI*2;
        const double halfRaySpread = raySpread/2;
        int mapArraySize, outerMapArraySize;

};

Rays::Rays() {
    rayAmount = 8.0f;
    rayLenght = 200;
}

Rays::~Rays() {}


double Rays::lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

Vector4 Rays::getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
    double tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
    double uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
    double bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);
    double retVal[3];
    // std::cout << bottom << " " << t;
    Vector4 test;
    if (bottom != 0) {
        double t = tTop/bottom;
        double u = uTop/bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            // retVal[0] = lerp(A.x, B.x, t);
            // retVal[1] = lerp(A.y, B.y, t);
            // retVal[2] = t;
            test.x = lerp(A.x, B.x, t);
            test.y = lerp(A.y, B.y, t);
            test.z = t;
            test.w = 5;
            // std::cout << std::endl << "test  " << retVal[2] << std::endl;
            // std::cout << lerp(A.x, B.x, t) << std::endl;
            return test;
        }
    }
    return test;
}



bool Rays::calcRayHits(int endRayLoc) {
    std::vector<Vector3> touches;
    Vector2 endRay = eindRay.at(endRayLoc);
    // Vector2 test[6];
    // test = map.returnWalls();
    // std::cout << map.wallVector;
    for (int i=0; i < mapArraySize; i++) {
        // std::cout << endRay.x << "  " << endRay.y << std::endl;
        Vector4 test;
        if (i < mapArraySize-1) {
            test = getIntersection(startRay, endRay, wallVector[i], wallVector[i+1]);
            // std::cout  << test.x << " " << test.y << " " << test.z << std::endl;
        } else {
            test = getIntersection(startRay, endRay, wallVector[i], wallVector[0]);
        }

        if (test.w == 5) {
            Vector3 valueVec;
            // std::cout << valueVec.z << " ";
            valueVec.x = test.x;
            valueVec.y = test.y;
            valueVec.z = test.z;
            touches.push_back(valueVec); 
        }

    }
    for (int i=0; i < outerMapArraySize; i++) {
        // std::cout << endRay.x << "  " << endRay.y << std::endl;
        Vector4 test;
        if (i < outerMapArraySize-1) {
            test = getIntersection(startRay, endRay, outerWallvector[i], outerWallvector[i+1]);
            // std::cout  << test.x << " " << test.y << " " << test.z << std::endl;
        } else {
            test = getIntersection(startRay, endRay, outerWallvector[i], outerWallvector[0]);
        }
        // std::cout << outerWallvector[i].x << "  " << outerWallvector[i].y << std::endl;

        if (test.w == 5) {
            Vector3 valueVec;
            // std::cout << valueVec.z << " ";
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

void Rays::draw() {
    for (int i=0; i < 8; i++) {
        Vector2 start = {startRay.x, startRay.y};
        if (hitCoordVec3.at(i).x == 0 && hitCoordVec3.at(i).y == 0 && hitCoordVec3.at(i).z == 0) {
            Vector2 eind = {eindRay.at(i).x, eindRay.at(i).y};
            DrawLineV(start, eind, WHITE);
        } else {
            Vector2 eind = {hitCoordVec3.at(i).x, hitCoordVec3.at(i).y};
            // if (eind.x == 0) {

            // } else {

            // }
            DrawLineV(start, eind, RED);
            // std::cout << hitCoordVec3.at(i).z << std::endl;
        }
        // Vector2 eind = {eindRay.at(i).x, eindRay.at(i).y};
        // DrawLineV(start, eind, WHITE);

    }
}

void Rays::update(Vector2 newStart, double newAngle) {
    eindRay = {};
    hitCoordVec3 = {};
    angle = newAngle;

    startRay.x = newStart.x;
    startRay.y = newStart.y;

    castRays();
    for (int i=0; i < 8; i++) {
        if (calcRayHits(i)) {
            hitCoordVec3.push_back(hitCoordVec);
        } else {
            hitCoordVec3.push_back({});
        }
        // std::cout << hit.x << std::endl;
        for (int i=0; i < 8; i++) {
            
        }
    }
}

void Rays::castRays() {
    for (int i=0; i < 8; i++) {
        double value;
        if (i != 0) {
            value = i/(rayAmount-1);
        } else {
            value = 0;
        }

        double rayAngle = lerp(halfRaySpread, -halfRaySpread, value);
        rayAngle += angle;

        float eindx = (startRay.x + sin(rayAngle) * rayLenght);
        float eindy = (startRay.y + cos(rayAngle) * rayLenght);

        Vector2 newEindRay = {eindx, eindy};

        eindRay.push_back(newEindRay);
    }
}
