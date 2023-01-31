#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cstdlib>

#include "gameMap2.h"
#include "car.h"
#include "geneticButton.h"
#include "visualizeNN.h"
#include "box.h"

class Genetic {
    public:
        Genetic();
        ~Genetic() {};
        void run(std::string newMaplocation);
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
        double timePast, fpsTimePast;

        bool server = false;
        bool showMenu = true;
        bool drawNNlocation = false;

        int bestCar = 0;
        int bestCarPoints;
        int generation;
        bool door = true;
        GameMapE2 map;
        GeneticMenu buttonMenu;
        nlohmann::json mapData;
        Vector2 testss = {100, 200};
        Box visualizeNNBox;
        
        std::string maplocation;
        std::vector<Vector2> box;
        std::vector<Vector2> nnlocation = {{200, 240}, {200, 680}, {720, 680}, {720, 240}};
};

Genetic::Genetic() {
    buttonMenu = GeneticMenu({{0, 900}, {2000, 900}, {2000, 1050}, {0,1050}});
    buttonMenu.addButton({{0,900}, {100, 900}, {100, 1050}, {0, 1050}}, "back", 20);
    buttonMenu.addButton({{100,900}, {400, 900}, {400, 1050}, {100, 1050}}, "Save Neuralnetwork", 20);
    buttonMenu.addButton({{400,900}, {700, 900}, {700, 1050}, {400, 1050}}, "Load Neuralnetwork", 20);

    network = GeneticNeuralNetwork({8, 12, 12, 6, 4});
    generation = 0;

    visualizeNNBox = Box(nnlocation.at(0), nnlocation.at(1), nnlocation.at(2), nnlocation.at(3));
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

    DrawText(TextFormat("generations: %f", float(generation)), 10, 60, 20, WHITE);
    DrawText(TextFormat("mutationRate: %f", mutationRate), 10, 80, 20, WHITE);
    DrawText(TextFormat("frame time past: %f", fpsTimePast), 10, 100, 20, WHITE);
    DrawText(TextFormat("total time past: %f", timePast), 10, 120, 20, WHITE);

    if (drawNNlocation) {
        DrawCircle(20, 880, 15, WHITE);
        if (box.size() > 1) {
            for (int i=0; i < box.size(); i++) {
                if (i == box.size()-1) {
                    DrawLineV(box.at(i), box.at(0), WHITE);
                } else {
                    DrawLineV(box.at(i), box.at(i+1), WHITE);
                }
            }
        }
    } else {
        DrawCircle(20, 880, 15, RED);
    }
    DrawText(TextFormat("draw NN location: "), 40, 873.5, 20, WHITE);

    map.draw();

    for (int i=0; i < cars.size(); i++) {
        cars.at(i).draw(false);
    }

    cars.at(bestCar).draw(true);
    buttonMenu.Draw();

    Vector2 test[4] = {nnlocation.at(0), nnlocation.at(1), nnlocation.at(2), nnlocation.at(3)};
    VisualiseGNN visualiseNetwork = VisualiseGNN(&cars.at(bestCar), test);
    visualiseNetwork.drawNeuralNetwork();

    DrawFPS(10,10);
    EndDrawing();
}

void Genetic::genCars() {
    cars.clear();
    
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["0"], {mapData["spawn"]["0"]["x"].get<float>(), mapData["spawn"]["0"]["y"].get<float>()}, maplocation);
        cars.push_back(car);
    }
}

void Genetic::SetCars(bool mutate) {
    std::ifstream f("NeuralNetworks/GNN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    f.close();
    
    cars.clear();
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["0"], {mapData["spawn"]["0"]["x"].get<float>(), mapData["spawn"]["0"]["y"].get<float>()}, maplocation); 
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
    std::ifstream f("NeuralNetworks/GNN.json");
    nlohmann::json networkData = nlohmann::json::parse(f);
    f.close();
    
    cars.clear();
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["0"], {mapData["spawn"]["0"]["x"].get<float>(), mapData["spawn"]["0"]["y"].get<float>()}, maplocation); 
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

    cars.clear();   
    for (int i=0; i < 100; i++) {
        GCar car = GCar(map, mapData["direction"]["0"], {mapData["spawn"]["0"]["x"], mapData["spawn"]["0"]["y"]}, maplocation); 

        car.network.loadNeuralNetwork(networkData);
        if (i == 0) {

        } else {
            car.network.mutate(mutationRate);
        }
        cars.push_back(car);
    }
}

void Genetic::Start() {
    std::ifstream f(maplocation);
    mapData = nlohmann::json::parse(f); 
    f.close();

    map.setMap(mapData);

    genCars();
}

void Genetic::loadNN() {
}

void Genetic::Update(double deltaTime) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (buttonMenu.buttons.at(0).checkCollisionButton(GetMousePosition())) {
            door = false;
        } else if (buttonMenu.buttons.at(1).checkCollisionButton(GetMousePosition())) {
            cars.at(bestCar).network.saveNeuralNetwork();
        } else if (buttonMenu.buttons.at(2).checkCollisionButton(GetMousePosition())) {
            loadNNCars();
        } else if (sqrt(pow(GetMousePosition().x-20, 2) + pow(GetMousePosition().y-880, 2)) <= 15) {
            if (drawNNlocation) {
                drawNNlocation = false;
            } else {
                drawNNlocation = true;
            }
        }
    }

    if (IsKeyPressed(KEY_ENTER)) {
        cars.at(bestCar).network.saveNeuralNetwork();
        loadNNCars();
    } else if (IsKeyPressed(KEY_LEFT_SHIFT)) {
        ResetCars();
    } else if (IsKeyPressed(KEY_Q)) {
        mutationRate += 0.05;
    } else if (IsKeyPressed(KEY_E)) {
        mutationRate -= 0.05;
    } else if (IsKeyPressed(KEY_R)) {
        mutationRate += 0.001;
    } else if (IsKeyPressed(KEY_T)) {
        mutationRate -= 0.001;
    } else if (IsKeyPressed(KEY_SPACE)) {
        genCars();
    }
    if (drawNNlocation) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            box.push_back(GetMousePosition());
        } else if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            if (box.size() != 0) {
                box.pop_back();
            }
        }

        if (box.size() == 4) {
            nnlocation = box;
        }
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
                mutationRate = 0.01;
            }
            SetCars(true);
        } else {
            network = cars.at(bestCar).network;
            cars.at(bestCar).network.saveNeuralNetwork();
            ResetCars();
        }
    } else if (cars.at(bestCar).collectedPoints >= (map.points.size()-1)*3) {
        network = cars.at(bestCar).network;
        cars.at(bestCar).network.saveNeuralNetwork();
        mutationRate -= 0.01;
        if (mutationRate < 0) {
            mutationRate = 0.01;
        }
        SetCars(true);
    }

    for (int i=0; i < cars.size(); i++) {
        cars.at(i).update(deltaTime);
    }
}   

void Genetic::run(std::string newMaplocation) {
    maplocation = newMaplocation;
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "car");
    SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(60);
    Start();
    while (!WindowShouldClose() && door){
        double deltaTime = GetFrameTime();
        fpsTimePast += 1/60.0f;
        timePast += deltaTime;
        Update(1/60.0f);
        Render();
    }

    CloseWindow();
}