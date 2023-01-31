#include <vector>
#include <raylib.h>

class Box {
    public:
        Box(Vector2 a = {0, 0}, Vector2 b = {0, 0}, Vector2 c = {0, 0}, Vector2 d = {0, 0});
        void draw();
    private:   
        Vector2 border[4];
};

Box::Box(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
    border[0] = a;
    border[1] = b;
    border[2] = c;
    border[3] = d;
}

void Box::draw() {
    for (int i=0; i < 4; i++) {
        if (i == 3) {
            DrawLineV(border[i], border[0], WHITE);
        } else {
            DrawLineV(border[i], border[i+1], WHITE);
        }
    }
}