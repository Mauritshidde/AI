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

std::vector<std::vector<double>> weights;
std::vector<double> biases;
NeuralNetwork network({4, 6, 8});


bool server = false;

int bestCar = 0;
int bestCarPoints;

GameMapE map;
// Car car(Vector2{screenWidth/2, screenHeight/2});

void SetCars(nlohmann::json data, bool mutate) {
    cars.clear();
    for (int i=0; i < 300; i++) {
        // for (int i=0; i < map.wallVectorVec.size(); i++) {
        //     std::cout << map.wallVectorVec.at(i).x << " xs " << map.wallVectorVec.at(i).y << "  y ";

        // }

        Car car(map.spawn, 1, map.wallVectorVec, map.arraySize, map.outerWall, map.outerSize, data["direction"], map.points);
        if (mutate) {
            // std::cout << "ja";
            if (i ==0) {
                car.network.setNN(network);
            } else {
                car.network.mutate(network, 1);
            }
        }
        cars.push_back(car);
    }
}

void ResetCars(nlohmann::json data) {
    cars.clear();
    for (int i=0; i < 300; i++) {
        Car car(map.spawn, 1, map.wallVectorVec, map.arraySize, map.outerWall, map.outerSize, data["direction"], map.points);
        if (i ==0) {
            car.network.setNN(network);
        } else {
            car.network.mutate(network, 1);
        }
        cars.push_back(car);

    }
}

void Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);

    map.draw();
    // car.draw();
    
    
    for (int i=0; i < cars.size(); i++) {
        if (cars.at(i).collectedPoints !=0) {
            // std::cout << cars.at(i).collectedPoints << std::endl;
        }
        if (bestCarPoints == 0) {
            bestCarPoints = cars.at(i).collectedPoints;
            bestCar = i;
        } if (cars.at(i).collectedPoints > bestCarPoints) {
            bestCarPoints = cars.at(i).collectedPoints;
            bestCar = i;
        }
    }
    // std::cout << cars.at(bestCar).collectedPoints << "  " <<bestCarPoints << " most points" << std::endl;
    for (int i=0; i < cars.size(); i++) {
        // if (cars.at(i).alive) {
        //     cars.at(i).draw();
        // }
        cars.at(i).draw(false);
    }
    cars.at(bestCar).draw(true);
    
    DrawFPS(10,10);
    EndDrawing();
}

void Start() {
    std::ifstream f("example.json");
    nlohmann::json data = nlohmann::json::parse(f);

    map.setMap(data);

    SetCars(data, false);
}

void Update(double deltaTime) {
    // car.update(deltaTime);
    // int bestCar;
    // for (int i=0; i < cars.size(); i++) {
    //     bestCar
    // }
    if (IsKeyPressed(KEY_ENTER)) {
        // weights.clear();
        // biases.clear();
        // for (int i=0; cars.at(bestCar).network.levels.size(); i++) {
        //     weights = cars.at(bestCar).network.levels.at(i).weights;
        // }
        // cars.at(bestCar).network.saveNN();

        network = cars.at(bestCar).network;

        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        SetCars(data, true);
    } else if (IsKeyPressed(KEY_LEFT_SHIFT)) {
        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        ResetCars(data);
    } else if (IsKeyPressed(KEY_RIGHT_SHIFT)) {
        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        SetCars(data, false);
    }

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