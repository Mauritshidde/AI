#include <cmath>
#include <raylib.h>

#include "ray.h"

class Sensor {
    public:
        Sensor(Vector2 position);
        void update();
        void draw();
    private:
        Ray rays[8];
        Vector2 start;
};

Sensor::Sensor(Vector2 position) {
    start = position;
    for (int i=0; i < 8; i++) {
        Ray ray(start);
    }
}

void Sensor::update(Vector2 eind) {
    for (int i=0; i < 8; i++) {
        rays[i].update(eind);
    }
}

void draw() {
    DrawLineV(start, eind, WHITE);
}