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

// Car* car;

std::vector<Car> cars;
// std::vector<std::vector<double>> weights;
// std::vector<double> biases;

// NeuralNetwork network({8, 6, 4});
// double mutationRate = 0.3;

bool server = false;
std::vector<double> previousMove;
float epsilon = 1;
int generation = 0;
GameMapE* map = new GameMapE();
// std::unique_ptr<Car> car(new Car(map, 3, {200, 200}));
Car* car = new Car(map, 3, {200, 200});
// map = GameMapE

std::ifstream f4("example.json");
nlohmann::json data4 = nlohmann::json::parse(f4);

// Car car(Vector2{screenWidth/2, screenHeight/2});


// void SetCars(nlohmann::json data, bool mutate) {

// }

// void ResetCars(nlohmann::json data) {

// }

void SetCar(nlohmann::json data, double epsilon) {
    // std::unique_ptr<Car> car(new Car(map, data["direction"]));
    // delete car;
    // car->~Car();
    // car.release();
    // delete car;
    // car = NULL;
    int value2 = data["spawn"]["lenght"].get<int>();
    int value = rand() % value2;
    // car = new Car(map, data["direction"][std::to_string(0)].get<float>(), map->spawns.at(0));
    car->restartLocation(data["direction"][std::to_string(value)].get<float>(), data["spawn"][std::to_string(value)]["firstcheckpoint"].get<float>(), map->spawns.at(value), epsilon);
    // float val = data["spawn"][std::to_string(value)].get<float>();
    // float val = data["spawn"][std::to_string(value)].get<float>();
    // std::cout << value << std::endl;
    // car.reset(new Car(map, data["direction"][std::to_string(value)].get<float>(), map->spawns.at(value)));
    // car = new Car(map, data["direction"]);
    
    // car->setSpawn(map->spawn, data["direction"]);
    // cars.clear();
    // // cars.pop_back();
    // // cars.pop_back();
    // for (int i=0; i < 2; i++) {
    //     Car car(map, data["direction"]);
    //     cars.push_back(car);
    // }
}

void CheckCar() {
    if (!car->alive) {
        std::ifstream f("example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        f.close();
        // cars.at(1).Qtable.Reward(true, cars.at(1).returnPreviousStates());
        // car->Qtable.Reward(true, car->returnPreviousStates());
        // cars.at(1).Qtable.saveQtable();
        // car->Qtable.saveQtable();
        SetCar(data, epsilon);
        generation++;
        if (generation == 200) {
            epsilon -= 0.1;
            if (epsilon < 0) {
                epsilon = 0;
            }
            // cars.at(1).Qtable.SetEpsilon(epsilon);
            // car->Qtable.SetEpsilon(epsilon);
            generation = 0;
        }
    } else {
        // std::vector<std::vector<double>> *previousStates = cars.at(1).returnPreviousStates();
        // cars.at(1).Qtable.Reward(false, cars.at(1).returnPreviousStates());
        // car->Qtable.Reward(false, car->returnPreviousStates());
    }
}

class VisualiseNN {
    public:
        VisualiseNN();
        void DrawNeuralNetwork();
        std::vector<std::vector<Vector2>> neuronLocation;
};

VisualiseNN::VisualiseNN() {
    std::vector<Vector2> firstLayerLocation;
    for (int i=0; i < car->neuralNetwork.levels.at(0).levelInputCount; i++) {
        Vector2 location = {180 ,float(200+i*30)};
        firstLayerLocation.push_back(location);
    }
    neuronLocation.push_back(firstLayerLocation);
    for (int j=0; j < car->neuralNetwork.levels.size(); j++) {
        std::vector<Vector2> layerNeuronLocation;
        for (int i=0; i < car->neuralNetwork.levels.at(j).weights.size(); i++) {
            Vector2 location = {float(290+j*110), float(200+i*30)};
            layerNeuronLocation.push_back(location);
        }
        neuronLocation.push_back(layerNeuronLocation);
    }
}

void VisualiseNN::DrawNeuralNetwork() {
    for (int i=0; i < neuronLocation.size(); i++) {
        for (int j=0; j < neuronLocation.at(i).size(); j++) {
            if (i == 0) {
                if (car->neuralNetwork.networkInput.at(j) >= 0.5) {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, RED); 
                } else {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, WHITE); 
                }
            } else {
                if (car->neuralNetwork.levels.at(i-1).levelNeuronOutputValue.at(j) >= 0.5) {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, RED); 
                } else {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, WHITE); 
                }
            }
        }
    }
    
    for (int i=0; i < car->neuralNetwork.levels.size(); i++) {
        for (int j=0; j < car->neuralNetwork.levels.at(i).weights.size(); j++) {
            for (int k=0; k < car->neuralNetwork.levels.at(i).weights.at(j).size(); k++) {
                if (car->neuralNetwork.levels.at(i).weights.at(j).at(k) >= 0){
                    DrawLineV(neuronLocation.at(i+1).at(j), neuronLocation.at(i).at(k), RED);
                } else {
                    DrawLineV(neuronLocation.at(i+1).at(j), neuronLocation.at(i).at(k), WHITE);
                }
            }  
        }
    }
}

void Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);

    map->draw();
    // cars.at(1).draw(false);
    car->draw(false);
    // std::string = std::to_string(generation);
    DrawText("ja", 600, 540, 10, BLACK);
    DrawText(TextFormat("%i", generation), 10, 40, 20, WHITE);
    DrawText(TextFormat("%f", epsilon), 10, 60, 20, WHITE);
    DrawText(TextFormat("%i", car->currentPoints), 10, 80, 20, WHITE);
    VisualiseNN visualiseNetwork = VisualiseNN();
    visualiseNetwork.DrawNeuralNetwork();
    DrawFPS(10,10);
    EndDrawing();

    CheckCar();
    
}

void Start() {
    std::ifstream f("example.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    // Button2 saveButton = Button2({500,200}, {100, 100});
    map->setMap(data);
    // car = new Car(map, data["direction"]);
    
    SetCar(data, epsilon);
    // SetCars(data, false);
}

void Update(double deltaTime) {

    // for (int i=0; i < cars.size(); i++) {
    //     cars.at(i).update(deltaTime);
    // }
    // cars.at(1).update(deltaTime);
    // cars.at(1).update(deltaTime);
    // cars.at(1).update(deltaTime);
    std::ifstream f("NN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    if (IsKeyDown(KEY_LEFT_CONTROL)) {
        car->neuralNetwork.saveNeuralNetwork();
    }
    if (IsKeyDown(KEY_RIGHT_CONTROL)) {
        car->neuralNetwork.loadNeuralNetwork(networkData);
    }
    
    car->update(1.0f/60.0f, map);

}   

int main() {
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "car");
    // SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);

    Start();
    while (!WindowShouldClose()){
        // double deltaTime = GetFrameTime();
        Update(float(1.0/30.0));
        Render();
    }

    // map = NULL;
    delete map;
    map = NULL;
    
    CloseWindow();
    return 0;
}