#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "DeepNN/trainAI.h"
#include "menuButtons.h"
#include "draw.h"
#include "GeneticAI/genetic2.h"

const int screenWidth = 1980;
const int screenHeight = 1024;

std::vector<MenuButton> menuButtonVector;

Drawer draw;
TrainAI train;
Genetic gen;

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
    MenuButton button2 = MenuButton({screenWidth/2-200,300}, {screenWidth/2+200,300}, {screenWidth/2+200,400}, {screenWidth/2-200,400}, "Deep NN", 20);
    MenuButton button3 = MenuButton({screenWidth/2-200,500}, {screenWidth/2+200,500}, {screenWidth/2+200,600}, {screenWidth/2-200,600}, "Genetic NN", 20);
    MenuButton button4 = MenuButton({screenWidth/2-200,700}, {screenWidth/2+200,700}, {screenWidth/2+200,800}, {screenWidth/2-200,800}, "Qtable AI", 20);
    menuButtonVector.push_back(button1);
    menuButtonVector.push_back(button2);
    menuButtonVector.push_back(button3);
    menuButtonVector.push_back(button4);
}

void UpdateMenu() {
    
}

int main() {
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "menu");
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
    
    switch (choice) {
        case 0:
            draw.run();
            break;
        case 1:
            train.run();
            break;
        case 2:
            gen.run();
            break;
        case 3:
            break;
    }
    
    CloseWindow();
    return 0;
}