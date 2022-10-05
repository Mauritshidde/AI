#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "raygui.h"
#include "GameMap.h"
#include "QCar.h"


const int screenWidth = 1980;
const int screenHeight = 1024;
// std::vector<Car> cars;
std::vector<Car> cars;
// std::vector<std::vector<double>> weights;
// std::vector<double> biases;

// NeuralNetwork network({8, 6, 4});
// double mutationRate = 0.3;

bool server = false;
std::vector<double> previousMove;
float epsilon = 1;
int generation = 0;
GameMapE map;

std::ifstream f4("example.json");
nlohmann::json data4 = nlohmann::json::parse(f4);
// Car car(Vector2{screenWidth/2, screenHeight/2});


// void SetCars(nlohmann::json data, bool mutate) {

// }

// void ResetCars(nlohmann::json data) {

// }

void SetCar(nlohmann::json data) {
    cars.clear();
    // cars.pop_back();
    // cars.pop_back();
    for (int i=0; i < 2; i++) {
        Car car(map.spawn, 1, map.wallVectorVec, map.arraySize, map.outerWall, map.outerSize, data["direction"], map.points);
        cars.push_back(car);
    }
}

void Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);

    map.draw();
    cars.at(1).draw(false);
    // std::string = std::to_string(generation);
    DrawText("ja", 600, 540, 10, BLACK);
    DrawText(TextFormat("%i", generation), 10, 40, 20, WHITE);
    DrawText(TextFormat("%f", epsilon), 10, 60, 20, WHITE);

    DrawFPS(10,10);
    EndDrawing();

    if (!cars.at(1).alive) {
        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        cars.at(1).Qtable.Reward(true, cars.at(1).previousStates);
        cars.at(1).Qtable.saveQtable();
        SetCar(data);
        generation++;
        if (generation == 20000) {
            epsilon -= 0.1;
            if (epsilon < 0) {
                epsilon = 0;
            }
            cars.at(1).Qtable.SetEpsilon(epsilon);
            generation = 0;
        }
    } else {
        cars.at(1).Qtable.Reward(false, cars.at(1).previousStates);
    }
}

void Start() {
    std::ifstream f("example.json");
    nlohmann::json data = nlohmann::json::parse(f);
    // Button2 saveButton = Button2({500,200}, {100, 100});
    map.setMap(data);
    
    SetCar(data);
    // SetCars(data, false);
}

void Update(double deltaTime) {

    // for (int i=0; i < cars.size(); i++) {
    //     cars.at(i).update(deltaTime);
    // }
    cars.at(1).update(deltaTime);
    cars.at(1).update(deltaTime);
    
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