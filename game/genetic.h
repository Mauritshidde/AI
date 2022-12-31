#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cstdlib>

#include "raygui.h"
#include "GameMap2.h"
#include "GCar.h"
#include "geneticButton.h"

class Genetic {
    public:
        Genetic();
        void Render();
        void Update(double deltaTime);
        void Start();
        void run();
        void SetCars(nlohmann::json data, bool mutate);
        void ResetCars(nlohmann::json data);
        void genCars();
        const int screenWidth = 1980;
        const int screenHeight = 1024;
        std::vector<GCar> cars;

        std::vector<std::vector<double>> weights;
        std::vector<double> biases;
        GeneticNeuralNetwork network;
        double mutationRate = 0.3;

        bool server = false;

        int bestCar = 0;
        int bestCarPoints;
        bool door = true;
        GameMapE2 map;
        GeneticMenu buttonMenu;
};

Genetic::Genetic() {
    buttonMenu = GeneticMenu({{0, 900}, {2000, 900}, {2000, 1050}, {0,1050}});
    buttonMenu.addButton({{0,900}, {100, 900}, {100, 1050}, {0, 1050}}, "back", 20);
    buttonMenu.addButton({{100,900}, {400, 900}, {400, 1050}, {100, 1050}}, "Save Neuralnetwork", 20);
    buttonMenu.addButton({{400,900}, {700, 900}, {700, 1050}, {400, 1050}}, "Load Neuralnetwork", 20);

    network = GeneticNeuralNetwork({16, 6, 6, 6, 4});
}

void Genetic::Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);

    bestCar = 0;
    bestCarPoints = 0;
    for (int i=0; i < cars.size(); i++) {
        if (cars.at(i).collectedPoints > bestCarPoints) {
            bestCarPoints = cars.at(i).collectedPoints;
            bestCar = i;
        }
    }
    std::cout << bestCar <<  " "  << bestCarPoints << std::endl;
    std::cout << cars.at(0).collectedPoints <<  " "  << cars.at(0).currentPoints << std::endl;
    DrawText(TextFormat("%f", cars.at(bestCar).collectedPoints), 10, 60, 20, WHITE);
    DrawText(TextFormat("%f", cars.at(bestCar).currentPoints), 10, 80, 20, WHITE);

    map.draw();
    
    for (int i=0; i < cars.size(); i++) {
        cars.at(i).draw(false);
    }

    cars.at(bestCar).draw(true);
    buttonMenu.Draw();

    DrawFPS(10,10);
    EndDrawing();
}

void Genetic::genCars() {
    std::ifstream f("maps/example.json");
    nlohmann::json data = nlohmann::json::parse(f);

    cars.clear();
    
    for (int i=0; i < 200; i++) {
        // srand(time(NULL));
        GCar car = GCar(map, data["direction"]["0"], {data["spawn"]["0"]["x"].get<float>(), data["spawn"]["0"]["y"].get<float>()});
        // car.network.randomize();
        cars.push_back(car);
    }
}

void Genetic::SetCars(nlohmann::json data, bool mutate) {
    std::ifstream f("NeuralNetworks/NN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);

    cars.clear();
    for (int i=0; i < 200; i++) {
        GCar car = GCar(map, data["direction"]["0"], {data["spawn"]["0"]["x"].get<float>(), data["spawn"]["0"]["y"].get<float>()}); 
        if (mutate) {
            if (i == 0) {
                car.network.loadNeuralNetwork(networkData);
            } else {
                car.network.mutate(networkData, mutationRate);
            }
        }
        cars.push_back(car);
    }
}

void Genetic::ResetCars(nlohmann::json data) {
    std::ifstream f("NeuralNetworks/NN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);

    cars.clear();
    for (int i=0; i < 200; i++) {
        GCar car = GCar(map, data["direction"]["0"], {data["spawn"]["0"]["x"], data["spawn"]["0"]["y"]}); 

        if (i ==0) {
            car.network.loadNeuralNetwork(networkData);
        } else {
            car.network.mutate(networkData, mutationRate);
        }
        cars.push_back(car);
    }
}


void Genetic::Start() {
    std::ifstream f("maps/example.json");
    nlohmann::json data = nlohmann::json::parse(f);
    map.setMap(data);

    // SetCars(data, false);
    genCars();
}

void Genetic::Update(double deltaTime) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (buttonMenu.buttons.at(0).checkCollisionButton(GetMousePosition())) {
            door = false;
        } else if (buttonMenu.buttons.at(1).checkCollisionButton(GetMousePosition())) {
            cars.at(bestCar).network.saveNeuralNetwork();
        } else if (buttonMenu.buttons.at(2).checkCollisionButton(GetMousePosition())) {
            std::ifstream f("NeuralNetworks/NN.json");
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
            
            std::ifstream l("maps/example.json");
            nlohmann::json data2 = nlohmann::json::parse(l);

            SetCars(data2, true);
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        std::cout << cars.at(bestCar).collectedPoints << " Ja " << bestCarPoints <<std::endl;
        cars.at(bestCar).network.saveNeuralNetwork();

        std::ifstream f("maps/example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        SetCars(data, true);
    } else if (IsKeyPressed(KEY_LEFT_SHIFT)) {
        std::ifstream f("maps/example.json");
        nlohmann::json data = nlohmann::json::parse(f);
        ResetCars(data);
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
    } else if (IsKeyPressed(KEY_SPACE)) {
        genCars();
    }

    for (int i=0; i < cars.size(); i++) {
        cars.at(i).update(deltaTime, &map);
    }
}   

void Genetic::run() {
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "car");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);
    Start();
    while (!WindowShouldClose() && door){
        double deltaTime = GetFrameTime();
        Update(deltaTime);
        Render();
    }

    CloseWindow();
}