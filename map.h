#include <raylib.h>

#include "wall.h"

class Map{
    public:
        Map();
        void draw();
    private:
        Vector2 vector[6] = {{200,100}, {400, 600},{700,800}, {700, 1100},{1100,300}, {1200, 600}};
};

Map::Map() {
    
}

void Map::draw() {
    DrawLineStrip(vector, 6, WHITE);
}