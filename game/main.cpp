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
#include "menu.h"

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
std::vector<MenuButton> menuButtonVector;
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

void RenderMenu() {
    const Color backgroundColor = BLACK;
    
    BeginDrawing();
    ClearBackground(backgroundColor);
    for (int i=0; i < menuButtonVector.size(); i++) {
        menuButtonVector.at(i).Draw();
    }
    DrawFPS(10,10);
    EndDrawing();
}

void StartMenu() {
    MenuButton button1 = MenuButton({screenWidth/2-200,100}, {screenWidth/2+200,100}, {screenWidth/2+200,200}, {screenWidth/2-200,200}, "map drawer", 20);
    MenuButton button2 = MenuButton({screenWidth/2-200,300}, {screenWidth/2+200,300}, {screenWidth/2+200,400}, {screenWidth/2-200,400}, "train AI", 20);
    MenuButton button3 = MenuButton({screenWidth/2-200,500}, {screenWidth/2+200,500}, {screenWidth/2+200,600}, {screenWidth/2-200,600}, "run AI", 20);
    menuButtonVector.push_back(button1);
    menuButtonVector.push_back(button2);
    menuButtonVector.push_back(button3);
}

void UpdateMenu() {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout << "ja";
    }
    if (IsKeyPressed(KEY_U)) {
        std::cout << "ja";
        
    }
}

bool CheckCollisionRectangle(Vector2 coordM, Vector2 coordA, Vector2 coordB, Vector2 coordD) {
    Vector2 AM = {coordM.x-coordA.x, coordM.y-coordA.y};
    Vector2 AB = {coordB.x-coordA.x, coordB.y-coordA.y};
    Vector2 AD = {coordD.x-coordA.x, coordD.y-coordA.y};

    double AMAB  = AM.x * AB.x + AM.y * AB.y;           // AM * AB
    double ABAB  = AB.x * AB.x + AB.y * AB.y;           // AB * AB
    double AMAD  = AM.x * AD.x + AM.y * AD.y;           // AM * AD
    double ADAD  = AD.x * AD.x + AD.y * AD.y;           // AD * AD

    if (0 < AMAB && AMAB < ABAB) {
        if (0 < AMAD && AMAD < ADAD) {
            return true;
        }
    }
    return false;
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
// bool UpdateMenu(double deltaTime) {
//     if (IsKeyPressed(MOUSE_BUTTON_LEFT)) {
//         std::cout << "ja";
//         return false;
//     }
//     return true;
// }

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

int main() {
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "menu");
    SetTargetFPS(60);
    bool notChosenMenu = true;
    StartMenu();
    while (notChosenMenu) {
        if (IsKeyPressed(KEY_A)) {
            notChosenMenu = false;
            break;
        } 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i=0; i < menuButtonVector.size(); i++) {
                if (CheckCollisionRectangle(GetMousePosition(), menuButtonVector.at(i).menuBox.at(0), menuButtonVector.at(i).menuBox.at(1), 
                                            menuButtonVector.at(i).menuBox.at(3))) {
                    notChosenMenu = false;
                    break;
                }
            }
        }
        UpdateMenu();
        RenderMenu();
    }

    CloseWindow();
    
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