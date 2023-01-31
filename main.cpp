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
#include "GeneticAI/genetic.h"
#include "QtableAI/QtableAI.h"
#include "selectMap.h"

const int screenWidth = 1980;
const int screenHeight = 1024;

std::vector<MenuButton> menuButtonVector;

Drawer draw;
TrainAI train;
Genetic gen;

void renderMenu() { // draw the menu items
    const Color backgroundColor = BLACK;
    
    BeginDrawing();
    ClearBackground(backgroundColor);
    for (int i=0; i < menuButtonVector.size(); i++) {
        menuButtonVector.at(i).draw();
    }

    DrawFPS(10,10);
    EndDrawing();
}

void startMenu() { // make the menu at the start of the program
    MenuButton button1 = MenuButton({screenWidth/2-200,100}, {screenWidth/2+200,100}, {screenWidth/2+200,200}, {screenWidth/2-200,200}, "map drawer", 20);
    MenuButton button2 = MenuButton({screenWidth/2-200,300}, {screenWidth/2+200,300}, {screenWidth/2+200,400}, {screenWidth/2-200,400}, "Deep NN", 20);
    MenuButton button3 = MenuButton({screenWidth/2-200,500}, {screenWidth/2+200,500}, {screenWidth/2+200,600}, {screenWidth/2-200,600}, "Genetic NN", 20);
    MenuButton button4 = MenuButton({screenWidth/2-200,700}, {screenWidth/2+200,700}, {screenWidth/2+200,800}, {screenWidth/2-200,800}, "Qtable AI", 20);
    menuButtonVector.push_back(button1);
    menuButtonVector.push_back(button2);
    menuButtonVector.push_back(button3);
    menuButtonVector.push_back(button4);
}

int main() {
    InitWindow(screenWidth, screenHeight, "menu");
    SetTargetFPS(60);
    bool notChosenMenu = true;
    int choice;
    startMenu();
    while (notChosenMenu) { // run this until an action is chosen from the menu or escape is pressed
        if (IsKeyPressed(KEY_A)) {
            notChosenMenu = false;
            break;
        } 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i=0; i < menuButtonVector.size(); i++) {
                if (menuButtonVector.at(i).checkCollisionRectangle(GetMousePosition())) {
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
        
        renderMenu();
    }

    CloseWindow();
    
    std::string maplocation;

    switch (choice) { // run the script of the chosen option
        case 0:
            draw.run();
            break;
        case 1:
            train.run();
            break;
        case 2:
            maplocation = runhjk();
            gen.run(maplocation);
            break;
        case 3:
            runrun();
            break;
    }
    
    CloseWindow();
    return 0;
}