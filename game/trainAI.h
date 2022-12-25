#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "raygui.h"
#include "GameMap.h"
#include "visualizeNN.h"

const int screenWidth = 1980;
const int screenHeight = 1024;

std::vector<Car> cars;

bool server = false;
std::vector<double> previousMove;
float epsilon = 1;
int generation = 0;
GameMapE* map = new GameMapE();
Car* car = new Car(map, 3, {200, 200});

std::ifstream f4("maps/example.json");
nlohmann::json data4 = nlohmann::json::parse(f4);

void SetCar(nlohmann::json data, double epsilon) {
    int value2 = data["spawn"]["lenght"].get<int>();
    int value = rand() % value2;
    car->restartLocation(data["direction"][std::to_string(value)].get<float>(), data["spawn"][std::to_string(value)]["firstcheckpoint"].get<float>(), map->spawns.at(value), epsilon);
}

void CheckCar() {
    if (!car->alive) {
        std::ifstream f("maps/example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        f.close();
        SetCar(data, epsilon);
        generation++;
        if (generation >= 200) {
            epsilon -= 0.1;
            if (epsilon < 0) {
                epsilon = 0;
            }
            generation = 0;
        }
    } else {
    }
}

void Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);

    map->draw();
    car->draw(false);
    DrawText("ja", 600, 540, 10, BLACK);
    DrawText(TextFormat("%i", generation), 10, 40, 20, WHITE);
    DrawText(TextFormat("%f", epsilon), 10, 60, 20, WHITE);
    DrawText(TextFormat("%i", car->currentPoints), 10, 80, 20, WHITE);
    VisualiseNN visualiseNetwork = VisualiseNN(car);
    visualiseNetwork.DrawNeuralNetwork();
    DrawFPS(10,10);
    EndDrawing();

    CheckCar();
    
}

void Start() {
    std::ifstream f("maps/example.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    map->setMap(data);
    
    SetCar(data, epsilon);
    
}

void Update(double deltaTime) {
    std::ifstream f("NeuralNetworks/NN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    if (IsKeyPressed(KEY_LEFT_CONTROL)) {
        car->neuralNetwork.saveNeuralNetwork();
    }
    if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
        car->neuralNetwork.loadNeuralNetwork(networkData);
        std::ifstream f("maps/example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        f.close();
        SetCar(data, epsilon);
    }
    
    car->update(1.0f/60.0f, map);

}   

int trainAI() {
    srand(time(NULL));
    
    InitWindow(screenWidth, screenHeight, "train Ai");

    Start();
    while (!WindowShouldClose()){
        Update(float(1.0/60.0));
        Render();
    }

    delete map;
    map = NULL;
    
    CloseWindow();
    return 0;
}