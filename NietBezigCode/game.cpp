#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "raygui.h"
#include "car.h"
#include "GameMap.h"
// #include "button.h"

const int screenWidth = 1980;
const int screenHeight = 1024;
std::vector<Car> cars;

std::vector<std::vector<double>> weights;
std::vector<double> biases;
// Button2 saveButton({0,0}, {0,0});
NeuralNetwork network({8, 6, 4});
double mutationRate = 0.3;

bool server = false;

int bestCar = 0;
int bestCarPoints;

GameMapE map;
// Car car(Vector2{screenWidth/2, screenHeight/2});

void SetCars(nlohmann::json data, bool mutate) {
    cars.clear();
    for (int i=0; i < 200; i++) {
        // for (int i=0; i < map.wallVectorVec.size(); i++) {
        //     std::cout << map.wallVectorVec.at(i).x << " xs " << map.wallVectorVec.at(i).y << "  y ";

        // }
        
        Car car(map.spawn, 1, map.wallVectorVec, map.arraySize, map.outerWall, map.outerSize, data["direction"], map.points);
        if (mutate) {
            // std::cout << "ja";
            if (i ==0) {
                car.network.setNN(network);
            } else {
                car.network.mutate(network, mutationRate);
            }
        }
        cars.push_back(car);
    }
}

void ResetCars(nlohmann::json data) {
    cars.clear();
    for (int i=0; i < 200; i++) {
        Car car(map.spawn, 1, map.wallVectorVec, map.arraySize, map.outerWall, map.outerSize, data["direction"], map.points);
        if (i ==0) {
            car.network.setNN(network);
        } else {
            car.network.mutate(network, mutationRate);
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
    DrawRectangleV({500,200}, {80, 80}, ORANGE);
    DrawText("reload Button", 510, 240, 10, BLACK);

    DrawRectangleV({800,500}, {80, 80}, ORANGE);
    DrawText("Load NN", 810, 540, 10, BLACK);
    bestCar = 0;
    bestCarPoints = 0;
    for (int i=0; i < cars.size(); i++) {
        if (cars.at(i).collectedPoints !=0) {
            // std::cout << cars.at(i).collectedPoints << std::endl;
        }
        // if (bestCarPoints == 0) {
        //     bestCarPoints = cars.at(i).collectedPoints;
        //     bestCar = i;
        // } 
        if (cars.at(i).collectedPoints > bestCarPoints) {
            bestCarPoints = cars.at(i).collectedPoints;
            bestCar = i;
        }
    }
    // for (int i=0; i < cars.at(bestCar).outputsbool.size(); i++) {
    //     std:: cout << cars.at(bestCar).outputsbool.at(i) << " ja "; 
    // }
    // std::cout << std::endl;
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
    // Button2 saveButton = Button2({500,200}, {100, 100});
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
        std::cout << cars.at(bestCar).collectedPoints << " Ja " << bestCarPoints <<std::endl;
        network = cars.at(bestCar).network;
        cars.at(bestCar).network.saveNN();

        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        SetCars(data, true);
    } else if (IsKeyPressed(KEY_LEFT_SHIFT)) {
        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        ResetCars(data);
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), {500, 200, 80, 80})) {
            std::ifstream f("example.json");
            nlohmann::json data = nlohmann::json::parse(f);
            SetCars(data, false);
        } else if (CheckCollisionPointRec(GetMousePosition(), {800, 500, 80, 80})) {
            std::ifstream f("NN.json");
            nlohmann::json data = nlohmann::json::parse(f);
            
            int lenght1 = data["weights"]["lenght"].get<int>();
            int lenght2 = data["biases"]["lenght"].get<int>();

            for (int i=0; i < lenght1; i++) {
                int lenghti = data["weights"][std::to_string(i)]["lenght"].get<int>();
                for (int j=0; j < lenghti; j++) {
                    int lenghtj = data["weights"][std::to_string(i)][std::to_string(j)]["lenght"].get<int>();
                    for (int k=0; k < lenghtj; k++) {
                        network.levels.at(i).weights.at(j).at(k) = data["weights"][std::to_string(i)][std::to_string(j)][std::to_string(k)].get<double>();
                    }
                }
                int lenghti2 = data["biases"][std::to_string(i)]["lenght"].get<int>();

                for (int j=0; j < lenghti2; j++) {
                    network.levels.at(i).biases.at(j) = data["biases"][std::to_string(i)][std::to_string(j)].get<double>();
                }
            }
            
            std::ifstream l("example.json");
            nlohmann::json data2 = nlohmann::json::parse(l);

            SetCars(data2, true);
        }
    } else if (IsKeyPressed(KEY_Q)) {
        mutationRate += 0.05;
        std::cout << mutationRate << std::endl;
    } else if (IsKeyPressed(KEY_E)) {
        mutationRate -= 0.05;
        std::cout << mutationRate << std::endl;
    } else if (IsKeyPressed(KEY_R)) {
        mutationRate += 0.001;
        std::cout << mutationRate << std::endl;
    } else if (IsKeyPressed(KEY_T)) {
        mutationRate -= 0.001;
        std::cout << mutationRate << std::endl;
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