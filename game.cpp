#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "car.h"
#include "GameMap.h"

const int screenWidth = 1980;
const int screenHeight = 1024;
std::vector<Car> cars;

bool server = false;

GameMapE map;
// Car car(Vector2{screenWidth/2, screenHeight/2});


void Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);

    map.draw();
    // car.draw();
    for (int i=0; i < cars.size(); i++) {
        cars.at(i).draw();
    }
    
    DrawFPS(10,10);
    EndDrawing();
}

void Start() {
    std::ifstream f("example.json");
    nlohmann::json data = nlohmann::json::parse(f);

    map.setMap(data);

    for (int i=0; i < 200; i++) {
        // for (int i=0; i < map.wallVectorVec.size(); i++) {
        //     std::cout << map.wallVectorVec.at(i).x << " xs " << map.wallVectorVec.at(i).y << "  y ";

        // }

        Car car(map.spawn, 1, map.wallVectorVec, map.arraySize, map.outerWall, map.outerSize, data["direction"]);
        cars.push_back(car);
    }
}

void Update(double deltaTime) {
    // car.update(deltaTime);
    for (int i=0; i < cars.size(); i++) {
        cars.at(i).update(deltaTime);
    }
}   

int main() {
    InitWindow(screenWidth, screenHeight, "car");
    SetWindowState(FLAG_VSYNC_HINT);

    Start();
    while (!WindowShouldClose()){
        double deltaTime = GetFrameTime();
        Update(deltaTime);
        Render();
    }

    CloseWindow();
    return 0;
}