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
        Vector2 *outerWallarr;
        int arraySize = 10;
        int outerSize = 10;
        Vector2 spawn;
        std::vector<Vector2> wallVectorVec, innerWall, outerWall;
        // std::vector<Vector2> wallVectorVec;
};

GameMapE::GameMapE() {
    
}

void GameMapE::draw() {
    DrawLineStrip(wallVector, arraySize, WHITE);
    DrawLineV(wallVector[0], wallVector[arraySize-1], WHITE);

    DrawLineStrip(outerWallarr, outerSize, WHITE);
    DrawLineV(outerWallarr[0], outerWallarr[outerSize-1], WHITE);
}

void GameMapE::setMap(nlohmann::json mapJson) {
    spawn.x = mapJson["spawn"]["x"];
    spawn.y = mapJson["spawn"]["y"];
    int size = mapJson["inner"]["lenght"].get<int>();
    int size2 = mapJson["outer"]["lenght"].get<int>();
    // std::cout << "ja " <<  size << " ja";

    wallVector = new Vector2[size];
    outerWallarr = new Vector2[size2];

    // std::cout << outerSize << std::endl;
    arraySize = size;
    outerSize = size2;

    for (int i=0; i < size; i++) {
        wallVector[i].x = mapJson["inner"][std::to_string(i)]["x"].get<double>();
        wallVector[i].y = mapJson["inner"][std::to_string(i)]["y"].get<double>();
        float x = mapJson["inner"][std::to_string(i)]["x"].get<float>();
        float y =  mapJson["inner"][std::to_string(i)]["y"].get<float>();
        wallVectorVec.push_back({x, y});
    }

    for (int i=0; i < outerSize; i++) {
        outerWallarr[i].x = mapJson["outer"][std::to_string(i)]["x"].get<double>();
        outerWallarr[i].y = mapJson["outer"][std::to_string(i)]["y"].get<double>();
        float x = mapJson["outer"][std::to_string(i)]["x"].get<float>();
        float y =  mapJson["outer"][std::to_string(i)]["y"].get<float>();
        outerWall.push_back({x, y});
    }

}
// Vector2 * GameMap::returnWalls() {
//     return wallVector;
// }