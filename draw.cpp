#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>


const int screenWidth = 1980;
const int screenHeight = 1024;
double rotation = 0;

bool inner, outer, spawn, direction;

bool server = false;
std::vector<Vector2> innerMap, outerMap;
Vector2 spawnLocation, angle;

void saveMap() {
    nlohmann::json j;
    j["inner"]["lenght"] = innerMap.size();
    j["outer"]["lenght"] = outerMap.size();

    for (int i=0; i < innerMap.size(); i++) {
        j["inner"][std::to_string(i)]["x"] = innerMap.at(i).x;
        j["inner"][std::to_string(i)]["y"] = innerMap.at(i).y;
    }

    for (int i=0; i < outerMap.size(); i++) {
        j["outer"][std::to_string(i)]["x"] = outerMap.at(i).x;
        j["outer"][std::to_string(i)]["y"] = outerMap.at(i).y;
    }

    j["spawn"]["x"] = spawnLocation.x;
    j["spawn"]["y"] = spawnLocation.y;

    j["direction"] = rotation;

    std::ofstream testfile;
    testfile.open ("example.json");
    testfile << j;
    testfile.close();
}

void Render() {
    const Color backgroundColor = BLACK;
    
    if (IsKeyDown(KEY_O)) {
        inner = true;
        outer = false;
        spawn = false;
        direction = false;
    } else if (IsKeyDown(KEY_P)) {
        inner = false;
        outer = true;
        spawn = false;
        direction = false;
    } else if (IsKeyDown(KEY_Q)) {
        inner = false;
        outer = false;
        spawn = true;
        direction = false;
    } else if (IsKeyDown(KEY_C)) {
        inner = false;
        outer = false;
        spawn = false;
        direction = true;
    }
    if (inner) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 innerPosition = GetMousePosition();
            innerMap.push_back(innerPosition);
        }
    } else if (outer) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 outerPosition = GetMousePosition();
            outerMap.push_back(outerPosition);
        }
    } else if (spawn) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            spawnLocation = GetMousePosition();
        }
        if (IsKeyDown(KEY_A)) {
            rotation -= 0.5;
        }
        if (IsKeyDown(KEY_D)) {
            rotation += 0.5;
        }
    } else if (direction) {
        if (IsKeyDown(KEY_A)) {
            rotation += 0.1;
        }
        if (IsKeyDown(KEY_D)) {
            rotation -= 0.1;
        }
    }
     

    BeginDrawing();
    ClearBackground(backgroundColor);

    DrawCircle(spawnLocation.x, spawnLocation.y, 4, RED);
    Rectangle rectangle = {spawnLocation.x, spawnLocation.y, 10, 20};
    DrawRectanglePro(rectangle, {5, 10}, rotation, WHITE);  
    
    if ( innerMap.size() == 1) {

    } else if (innerMap.size() == 2) {
        DrawLineV(innerMap.at(0), innerMap.at(1), RED);
    } else {
        for (int i=0; i < innerMap.size(); i++) {
            if (i == innerMap.size()-1) {
                DrawLineV(innerMap.at(i), innerMap.at(0), RED);
            } else {
                DrawLineV(innerMap.at(i), innerMap.at(i+1), RED);
            }
        }
    }

    if ( outerMap.size() == 1) {

    } else if (outerMap.size() == 2) {
        DrawLineV(outerMap.at(0), outerMap.at(1), RED);
    } else {
        for (int i=0; i < outerMap.size(); i++) {
            if (i == outerMap.size()-1) {
                DrawLineV(outerMap.at(i), outerMap.at(0), RED);
            } else {
                DrawLineV(outerMap.at(i), outerMap.at(i+1), RED);
            }
        }
    }
    if (IsKeyDown(KEY_ENTER)) {
        saveMap();
        // nlohmann::json j;
        // j["lenght"] = map.size();

        // for (int i=0; i < map.size(); i++) {
        //     std::cout << i << std::endl;
        //     j[std::to_string(i)]["x"] = map.at(i).x;
        //     j[std::to_string(i)]["y"] = map.at(i).y;

        //     std::ofstream testfile;
        //     testfile.open ("example.json");
        //     testfile << j;
        //     testfile.close();
        // }

        // std::ofstream myfile;
        // myfile.open ("example.txt");
        // for (int i=0; i < map.size(); i++) {
        //     myfile << map.at(i).x << "," << map.at(i).y << std::endl;
        // }
        // myfile.close();
    }
    // int a;
    // std::ifstream myfile;
    // myfile.open("example.txt");
    // bool door = true;
    
    

    // auto j3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");

    

    // write to a stream, or the same file
    // std::cout << j << std::endl; // print the json

    

    // std::ifstream f("example.json");
    // nlohmann::json data = nlohmann::json::parse(f);
    // std::cout << data << std::endl;
    
    // for (int i=0; i < screenWidth; i++) {
    //     for (int j=0; i < screenHeight; i++) {
    //         DrawLineV({i,i},{i+1, i+1}, BLUE);
    //     }
    // }


    DrawFPS(10,10);
    EndDrawing();
}

void Start() {
    inner = true;
    outer = false;
}

void Update(double deltaTime) {

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