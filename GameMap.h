#include <raylib.h>

class GameMapE {
    public:
        GameMapE();
        void draw();
        // Vector2 * returnWalls();
        Vector2 wallVector[6] = {{200,100}, {400, 600},{700,800}, {700, 1100},{1100,300}, {1200, 600}};
};

GameMapE::GameMapE() {
    
}

void GameMapE::draw() {
    DrawLineStrip(wallVector, 6, WHITE);
    DrawLineV(wallVector[0], wallVector[5], WHITE);
}

// Vector2 * GameMap::returnWalls() {
//     return wallVector;
// }