#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cstdlib>

#include "GameMap2.h"
#include "Car.h"
#include "geneticButton.h"
#include "visualizeNN.h"

class Genetic {
    public:
        Genetic();
        ~Genetic() {};
        void run();
    private:
        void Render();
        void Update(double deltaTime);
        void Start();
        void loadNN();
        void SetCars(bool mutate);
        void ResetCars();
        void loadNNCars();
        void genCars();

        const int screenWidth = 1980;
        const int screenHeight = 1024;
        std::vector<GCar> cars;

        std::vector<std::vector<double>> weights;
        std::vector<double> biases;
        GeneticNeuralNetwork network;
        double mutationRate = 0.7;

        bool server = false;

        int bestCar = 0;
        int bestCarPoints;
        int generation;
        bool door = true;
        GameMapE2 map;
        GeneticMenu buttonMenu;
        nlohmann::json mapData;
};

Genetic::Genetic() {
    buttonMenu = GeneticMenu({{0, 900}, {2000, 900}, {2000, 1050}, {0,1050}});
    buttonMenu.addButton({{0,900}, {100, 900}, {100, 1050}, {0, 1050}}, "back", 20);
    buttonMenu.addButton({{100,900}, {400, 900}, {400, 1050}, {100, 1050}}, "Save Neuralnetwork", 20);
    buttonMenu.addButton({{400,900}, {700, 900}, {700, 1050}, {400, 1050}}, "Load Neuralnetwork", 20);

    network = GeneticNeuralNetwork({8, 12, 12, 6, 4});
    generation = 0;

    std::ifstream f("maps/example.json");
    mapData = nlohmann::json::parse(f); 
    f.close();
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
    DrawText(TextFormat("%f", generation), 10, 60, 20, WHITE);
    DrawText(TextFormat("%f", mutationRate), 10, 80, 20, WHITE);

    map.draw();
    
    for (int i=0; i < cars.size(); i++) {
        cars.at(i).draw(false);
    }

    cars.at(bestCar).draw(true);
    buttonMenu.Draw();

    VisualiseGNN visualiseNetwork = VisualiseGNN(&cars.at(bestCar));
    visualiseNetwork.DrawNeuralNetwork();

    DrawFPS(10,10);
    EndDrawing();
}

void Genetic::genCars() {
    cars.clear();
    
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["19"], {mapData["spawn"]["19"]["x"].get<float>(), mapData["spawn"]["19"]["y"].get<float>()});
        cars.push_back(car);
    }
}

void Genetic::SetCars(bool mutate) {
    std::ifstream f("NeuralNetworks/GNN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    f.close();
    
    cars.clear();
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["19"], {mapData["spawn"]["19"]["x"].get<float>(), mapData["spawn"]["19"]["y"].get<float>()}); 
        if (mutate) {
            car.network.loadNeuralNetwork(networkData);
            if (i == 0 || i == 1) {

            } else {
                car.network.mutate(mutationRate);
            }
        }
        cars.push_back(car);
    }
}

void Genetic::loadNNCars() {
    std::ifstream f("NeuralNetworks/GNN2.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    f.close();
    
    cars.clear();
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["19"], {mapData["spawn"]["19"]["x"].get<float>(), mapData["spawn"]["19"]["y"].get<float>()}); 
        car.network.loadNeuralNetwork(networkData);
        if (i != 0) {
            car.network.mutate(0.1);
        }
        cars.push_back(car);
    }
}

void Genetic::ResetCars() {
    std::ifstream f("NeuralNetworks/GNN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    f.close();

    // std::ifstream r("NeuralNetworks/GNN.json");
    // nlohmann::json networkData = nlohmann::json::parse(r);
    // r.close();

    cars.clear();   
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["19"], {mapData["spawn"]["19"]["x"], mapData["spawn"]["19"]["y"]}); 

        car.network.loadNeuralNetwork(networkData);
        if (i == 0) {

        } else {
            car.network.mutate(mutationRate);
        }
        cars.push_back(car);
    }
}

void Genetic::Start() {
    map.setMap(mapData);

    genCars();
}

void Genetic::loadNN() {
}

void Genetic::Update(double deltaTime) {
    // std::cout << "ja0 " << std::endl;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (buttonMenu.buttons.at(0).checkCollisionButton(GetMousePosition())) {
            door = false;
        } else if (buttonMenu.buttons.at(1).checkCollisionButton(GetMousePosition())) {
            cars.at(bestCar).network.saveNeuralNetwork();
        } else if (buttonMenu.buttons.at(2).checkCollisionButton(GetMousePosition())) {
            // loadNN();
            loadNNCars();
            
            // std::ifstream l("maps/example.json");
            // nlohmann::json data2 = nlohmann::json::parse(l);
            // l.close();

            // SetCars(true);
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        cars.at(bestCar).network.saveNeuralNetwork();
        loadNNCars();
        // SetCars(true);
    } else if (IsKeyPressed(KEY_LEFT_SHIFT)) {
        ResetCars();
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

    int alive = 0;
    for (int i=0; i < cars.size(); i++) {
        if (cars.at(i).alive) {
            alive++; 
        }
    }
    if (alive == 0) {
        generation++;
        if (generation >= 5) {
            network = cars.at(bestCar).network;
            cars.at(bestCar).network.saveNeuralNetwork();
            mutationRate -= 0.01;
            if (mutationRate < 0) {
                mutationRate = 0;
            }
            SetCars(true);
        } else {
            network = cars.at(bestCar).network;
            cars.at(bestCar).network.saveNeuralNetwork();
            ResetCars();
        }
    }
    for (int i=0; i < cars.size(); i++) {
        cars.at(i).update(deltaTime);
    }
}   

void Genetic::run() {
    srand(time(NULL));
    // srand((unsigned) time(NULL));
    InitWindow(screenWidth, screenHeight, "car");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);
    Start();
    while (!WindowShouldClose() && door){
        double deltaTime = GetFrameTime();
        Update(1/60.0f);
        Render();
    }

    CloseWindow();
}