#include <raylib.h>
#include <vector>
#include <cmath>

#include <iostream>

void getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
    double tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
    double uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
    double bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);

    if (bottom != 0) {
        double t = tTop/bottom;
        double u = uTop/bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            double value[3];
            value[0] = lerp(A.x, B.x, t);
            value[1] = lerp(A.y, B.y, t);
            value[2] = t;
            return ;
        }
    }
}

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

class Rays {
    public:
        Rays();
        void update(Vector2 newStart, double newAngle);
        void draw();
    private:
        void castRays();
        Vector2 start;
        Vector2 eind;
        Vector2 startRay; 
        std::vector<Vector2> eindRay; 
        const double raySpread = M_PI*2;
        const double halfRaySpread = raySpread/2;
        double rayAmount = 8.0f;
        double angle;
        double rayLenght = 200;
        double rayAngle;
};

Rays::Rays() {

}

void Rays::draw() {
    for (int i=0; i < 8; i++) {
        start = {startRay.x, startRay.y};
        eind = {eindRay.at(i).x, eindRay.at(i).y};
        DrawLineV(start, eind, WHITE);
    }
}

void Rays::update(Vector2 newStart, double newAngle) {
    eindRay = {};
    angle = newAngle;

    startRay.x = newStart.x;
    startRay.y = newStart.y;

    for (int i=0; i < 8; i++) {
        double value;
        if (i != 0) {
            // value = i/(rayAmount-1);
            value = i/(rayAmount-1);
        } else {
            // value = 0.5/(rayAmount-1);
            value = 0;
        }

        double rayAngle = lerp(halfRaySpread, -halfRaySpread, value);
        rayAngle += angle;

        float eindx = (newStart.x + sin(rayAngle) * rayLenght);
        float eindy = (newStart.y + cos(rayAngle) * rayLenght);

        Vector2 newEindRay = {eindx, eindy};

        eindRay.push_back(newEindRay);

    }
}

void Rays::castRays() {
    startRay = {};
    for (int i=0; i < 8; i++) {
        double rayAngle = lerp(halfRaySpread, -halfRaySpread, i/(rayAmount-1));
        rayAngle += angle;
    }



    start.x = 0;
}
