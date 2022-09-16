#include <raylib.h>
#include <vector>
#include <nlohmann/json.hpp>


class GameMapE {
    public:
        GameMapE();
        void draw();
        void setMap(nlohmann::json mapJson);
        // Vector2 * returnWalls();
        Vector2 *wallVector;
        int arraySize = 10;
        std::vector<Vector2> wallVectorVec;
        // std::vector<Vector2> wallVectorVec;
};

GameMapE::GameMapE() {
    
}

void GameMapE::draw() {
    DrawLineStrip(wallVector, arraySize, WHITE);
    DrawLineV(wallVector[0], wallVector[5], WHITE);
}

void GameMapE::setMap(nlohmann::json mapJson) {
    int size = mapJson["lenght"].get<int>();
    std::cout << "ja " <<  size << " ja";
    wallVector = new Vector2[size];
    arraySize = size;

    for (int i=0; i < size; i++) {
        wallVector[i].x = mapJson[std::to_string(i)]["x"].get<double>();
        wallVector[i].y = mapJson[std::to_string(i)]["y"].get<double>();
        float x =mapJson[std::to_string(i)]["x"].get<float>();
        float y =  mapJson[std::to_string(i)]["y"].get<float>();
        wallVectorVec.push_back({x, y});
        // std::cout << wallVectorVec.at(i).x << " x " << wallVectorVec.at(i).y << "  y ";
    }

}
// Vector2 * GameMap::returnWalls() {
//     return wallVector;
// }