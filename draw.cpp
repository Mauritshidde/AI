#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>


const int screenWidth = 1980;
const int screenHeight = 1024;

bool server = false;
std::vector<Vector2> map;

void Render() {
    const Color backgroundColor = BLACK;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 position = GetMousePosition();
        map.push_back(position);
    } 

    BeginDrawing();
    ClearBackground(backgroundColor);

    if ( map.size() == 1) {

    } else if (map.size() == 2) {
        DrawLineV(map.at(0), map.at(1), RED);
    } else {
        for (int i=0; i < map.size(); i++) {
            if (i == map.size()-1) {
                DrawLineV(map.at(i), map.at(0), RED);
            } else {
                DrawLineV(map.at(i), map.at(i+1), RED);
            }
        }
    }
    if (IsKeyDown(KEY_ENTER)) {
        nlohmann::json j;
        j["lenght"] = map.size();

        for (int i=0; i < map.size(); i++) {
            std::cout << i << std::endl;
            j[std::to_string(i)]["x"] = map.at(i).x;
            j[std::to_string(i)]["y"] = map.at(i).y;

            std::ofstream testfile;
            testfile.open ("example.json");
            testfile << j;
            testfile.close();
        }
        // std::ofstream myfile;
        // myfile.open ("example.txt");
        // for (int i=0; i < map.size(); i++) {
        //     myfile << map.at(i).x << "," << map.at(i).y << std::endl;
        // }
        // myfile.close();
    }
    int a;
    std::ifstream myfile;
    myfile.open("example.txt");
    bool door = true;
    
    

    auto j3 = nlohmann::json::parse(R"({"happy": true, "pi": 3.141})");

    

    // write to a stream, or the same file
    // std::cout << j << std::endl; // print the json

    

    std::ifstream f("example.json");
    nlohmann::json data = nlohmann::json::parse(f);
    std::cout << data << std::endl;
    
    DrawFPS(10,10);
    EndDrawing();
}

void Start() {

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