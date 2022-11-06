#include <raylib.h>

class Button2 {
    public:
        Button2::Button2(Vector2 size, Vector2 position);
        void Button2::Draw(); 
        Rectangle rectangle;

    private:
};

Button2::Button2(Vector2 size, Vector2 position) {
    rectangle = {position.x, position.y, size.x, size.y};
}

void Button2::Draw() {
    DrawRectangleRec(rectangle, RED); 
}