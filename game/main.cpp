#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "trainAI.h"
#include "menuButtons.h"
#include "draw.h"
#include "genetic.h"

const int screenWidth2 = 1980;
const int screenHeight2 = 1024;

std::vector<MenuButton> menuButtonVector;

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
    MenuButton button1 = MenuButton({screenWidth2/2-200,100}, {screenWidth2/2+200,100}, {screenWidth2/2+200,200}, {screenWidth2/2-200,200}, "map drawer", 20);
    MenuButton button2 = MenuButton({screenWidth2/2-200,300}, {screenWidth2/2+200,300}, {screenWidth2/2+200,400}, {screenWidth2/2-200,400}, "train AI", 20);
    MenuButton button3 = MenuButton({screenWidth2/2-200,500}, {screenWidth2/2+200,500}, {screenWidth2/2+200,600}, {screenWidth2/2-200,600}, "run AI", 20);
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

int main() {
    srand(time(NULL));
    InitWindow(screenWidth2, screenHeight2, "menu");
    SetTargetFPS(60);
    bool notChosenMenu = true;
    int choice;
    StartMenu();
    while (notChosenMenu) {
        if (IsKeyPressed(KEY_A)) {
            notChosenMenu = false;
            break;
        } 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i=0; i < menuButtonVector.size(); i++) {
                if (menuButtonVector.at(i).CheckCollisionRectangle(GetMousePosition())) {
                    notChosenMenu = false;
                    choice = i;
                    break;
                }
            }
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            notChosenMenu = false;
            break;
        }
        
        UpdateMenu();
        RenderMenu();
    }

    CloseWindow();
    
    if (choice == 0) {
        drawMap();
    } else if (choice == 1) {
        trainAI();
    } else if (choice == 2) {
        Genetic gen;
        gen.run();
    }
    
    CloseWindow();
    return 0;
}