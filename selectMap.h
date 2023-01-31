#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <sstream>

#include "kiezmapMap.h"

const int screenWidth2 = 1980;
const int screenHeight2 = 1024;

std::vector<std::string> maps= {"map1", "map2", "example", "k"}; // vector of the name of the map files
std::vector<std::string> maplocations;
std::vector<MenuButton> mapButtons;
std::vector<Mapgen> mapdrawings;

void renderMaps() {
    const Color backgroundColor = BLACK;
    
    BeginDrawing();
    ClearBackground(backgroundColor);

    for (int i=0; i < mapButtons.size(); i++) {
        mapButtons.at(i).draw();
    }
    
    for (int i=0; i < mapdrawings.size(); i++) {
        mapdrawings.at(i).draw();
    }

    DrawFPS(10,10);
    EndDrawing();
}

void startmaps() {
    float padding = 100;
    float size = 400;
    float margine = (screenWidth2-padding)/maps.size();
    for (int i=0; i < maps.size(); i++) {
        MenuButton mapButton = MenuButton({padding+margine*i,300}, {padding+size+margine*i,300}, {padding+size+margine*i,700}, {padding+margine*i,700}, "", 20);
        mapButtons.push_back(mapButton);
    }

    for (int i=0; i < maps.size(); i++) {
        Mapgen map = Mapgen(400, 400, {padding+margine*i, 300});

        std::ostringstream oss;
        oss << "maps/" << maps.at(i) << ".json";
        std::string locationstring = oss.str();
        std::ifstream f(locationstring);
        nlohmann::json data = nlohmann::json::parse(f);
        f.close();
        maplocations.push_back(locationstring);

        map.setMap(data);
        map.update();
        mapdrawings.push_back(map);
    }   
}

void updatemaps() {
}

std::string runhjk() {
    InitWindow(screenWidth2, screenHeight2, "menu");
    SetTargetFPS(60);
    bool notChosenMenu = true;
    int choice;
    startmaps();
    while (notChosenMenu) {
        if (IsKeyPressed(KEY_A)) {
            notChosenMenu = false;
            break;
        } 
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i=0; i < mapButtons.size(); i++) {
                if (mapButtons.at(i).checkCollisionRectangle(GetMousePosition())) {
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
        
        updatemaps();
        renderMaps();
    }

    CloseWindow();

    return maplocations.at(choice);
}