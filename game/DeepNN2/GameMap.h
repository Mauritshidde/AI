#include <raylib.h>
#include <vector>
#include <nlohmann/json.hpp>


class GameMapE {
    public:
        GameMapE();
        void update();
        void draw();
        void setMap(nlohmann::json mapJson);
        int arraySize = 10;
        int outerSize = 10;
        Vector2 spawn;
        std::vector<Vector2> wallVectorVec, innerWall, outerWall, spawns, outerWall2, wallVectorVec2;
        std::vector<std::vector<Vector2>> points, points2;
};

GameMapE::GameMapE() {
    
}

void GameMapE::update() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    for (int i=0; i < wallVectorVec2.size(); i++) {
        float x = (wallVectorVec2.at(i).x/1980)*screenWidth;
        float y = (wallVectorVec2.at(i).y/1024)*screenHeight;
        wallVectorVec.at(i) = {x,y};
    }
    for (int i=0; i < outerWall2.size(); i++) {
        float x = (outerWall2.at(i).x/1980)*screenWidth;
        float y = (outerWall2.at(i).y/1024)*screenHeight;
        outerWall.at(i) = {x,y};
    }
    for (int i=0; i < points2.size(); i++) {
        float x = (points2.at(i).at(0).x/1980)*screenWidth;
        float y = (points2.at(i).at(0).y/1024)*screenHeight;

        float x2 = (points2.at(i).at(1).x/1980)*screenWidth;
        float y2 = (points2.at(i).at(1).y/1024)*screenHeight;

        points.at(i) = {{x,y}, {x2,y2}};
    }
}

void GameMapE::draw() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Vector2 wallVector[wallVectorVec.size()];
    Vector2 outerWallarr[outerWall.size()];

    for (int i=0; i < wallVectorVec.size(); i++) {
        float x = (wallVectorVec.at(i).x/1980)*screenWidth;
        float y = (wallVectorVec.at(i).y/1024)*screenHeight;
        wallVector[i] = {x,y};
        // wallVector[i] = wallVectorVec.at(i);
    }
    for (int i=0; i < outerWall.size(); i++) {
        float x = (outerWall.at(i).x/1980)*screenWidth;
        float y = (outerWall.at(i).y/1024)*screenHeight;
        outerWallarr[i] = {x,y};
        // outerWallarr[i] = outerWall.at(i);
    }

    DrawLineStrip(wallVector, arraySize, WHITE);
    DrawLineV(wallVector[0], wallVector[arraySize-1], WHITE);

    DrawLineStrip(outerWallarr, outerSize, WHITE);
    DrawLineV(outerWallarr[0], outerWallarr[outerSize-1], WHITE);
    for (int i=0; i < points.size(); i++) {
        DrawLine((points.at(i).at(0).x/1980)*screenWidth, (points.at(i).at(0).y/1024)*screenHeight, (points.at(i).at(1).x/1980)*screenWidth, (points.at(i).at(1).y/1024)*screenHeight, YELLOW);   
        // DrawLine(points.at(i).at(0).x, points.at(i).at(0).y, points.at(i).at(1).x, points.at(i).at(1).y, YELLOW);   

    }
}

void GameMapE::setMap(nlohmann::json mapJson) {
    for (int i=0; i < mapJson["spawn"]["lenght"].get<int>(); i++) {
        spawns.push_back({mapJson["spawn"][std::to_string(i)]["x"].get<float>(), mapJson["spawn"][std::to_string(i)]["y"].get<float>()});
    }
    int size = mapJson["inner"]["lenght"].get<int>();
    int size2 = mapJson["outer"]["lenght"].get<int>();
    int pointsSize = mapJson["points"]["lenght"].get<int>();
    
    arraySize = size;
    outerSize = size2;

    for (int i=0; i < size; i++) {
        float x = mapJson["inner"][std::to_string(i)]["x"].get<float>();
        float y =  mapJson["inner"][std::to_string(i)]["y"].get<float>();
        wallVectorVec.push_back({x, y});
    }

    for (int i=0; i < outerSize; i++) {
        float x = mapJson["outer"][std::to_string(i)]["x"].get<float>();
        float y =  mapJson["outer"][std::to_string(i)]["y"].get<float>();
        outerWall.push_back({x, y});
    }

    for (int i=0; i < pointsSize; i++) {
        float x = mapJson["points"][std::to_string(i)]["start"]["x"].get<float>();
        float y =  mapJson["points"][std::to_string(i)]["start"]["y"].get<float>();

        float x2 = mapJson["points"][std::to_string(i)]["end"]["x"].get<float>();
        float y2 =  mapJson["points"][std::to_string(i)]["end"]["y"].get<float>();

        points.push_back({{x, y}, {x2, y2}});
    }

    points2 = points;
    wallVectorVec2 = wallVectorVec;
    outerWall2 = outerWall;

}