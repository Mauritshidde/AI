#include <raylib.h>
// #include <vector>
#include <cmath>

#include <iostream>

#include "GameMap.h"


GameMapE map2;

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

Vector4 getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
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


class Rays {
    public:
        Rays();
        void update(Vector2 newStart, double newAngle);
        void draw();
    private:
        void calcRayHits();
        void castRays();

        std::vector<Vector2> eindRay; 
        Vector2 startRay;
        double rayAmount, angle, rayLenght, rayAngle;
        const double raySpread = M_PI*2;
        const double halfRaySpread = raySpread/2;

};

Rays::Rays() {
    rayAmount = 8.0f;
    rayLenght = 200;
}

void Rays::calcRayHits() {
    GameMapE map;
    std::vector<Vector3> touches;
    // Vector2 test[6];
    // test = map.returnWalls();
    // std::cout << map.wallVector;
    for (int i=0; i < 6; i++) {
        Vector4 test;
        if (i < 5) {
            test = getIntersection(startRay, eindRay.at(i), map.wallVector[i], map.wallVector[i+1]);
            // std::cout  << test.x << " " << test.y << " " << test.z << std::endl;
        } else {
            test = getIntersection(startRay, eindRay.at(i), map.wallVector[i], map.wallVector[0]);
        }

        if (test.w == 5) {
            Vector3 valueVec;
            std::cout << valueVec.z << " ";
            valueVec.x = test.x;
            valueVec.y = test.y;
            valueVec.z = test.z;
            touches.push_back(valueVec); 
        }
    }
}

void Rays::draw() {
    for (int i=0; i < 8; i++) {
        Vector2 start = {startRay.x, startRay.y};
        Vector2 eind = {eindRay.at(i).x, eindRay.at(i).y};
        DrawLineV(start, eind, WHITE);
    }
}

void Rays::update(Vector2 newStart, double newAngle) {
    eindRay = {};
    angle = newAngle;

    startRay.x = newStart.x;
    startRay.y = newStart.y;

    castRays();
    
    calcRayHits();
    for (int i=0; i < 8; i++) {

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
