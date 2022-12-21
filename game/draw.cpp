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

bool inner, outer, spawn, point, selectpoint;

bool server = false;
std::vector<bool> pointcolor;
std::vector<Vector2> innerMap, outerMap, points2;
std::vector<std::vector<Vector2>> points;
Vector2 spawnLocation, angle;
std::vector<Vector2> spawnLocations;
std::vector<double> rotations;
std::vector<int> firstCheckPoints;

class CheckPoints {
    public:
        CheckPoints();
        void addCheckPoint();

};

bool clickOnLine(Vector2 location, int i) {
    Vector2 startCoords = points.at(i).at(0);
    Vector2 endCoords = points.at(i).at(1);
    double factor = ((endCoords.y - startCoords.y)/(endCoords.x - startCoords.x));
    double b = startCoords.y - startCoords.x * factor;

    if (endCoords.x - startCoords.x < 20 && endCoords.x - startCoords.x > -20) {
        if (location.x >= startCoords.x-10 && location.x <= startCoords.x+10) {
            if (startCoords.y > endCoords.y) {
                if (location.y <= startCoords.y+10 && location.y >= endCoords.y-10) {
                    return true;
                }
            } else {
                if (location.y >= startCoords.y-10 && location.y <= endCoords.y+10) {
                    return true;
                }
            }
        }
    }
    if (endCoords.x > startCoords.x) {
        if (location.x >= startCoords.x-10 && location.x <= endCoords.x+10) {
            if (location.x * factor + b >= location.y-10 && location.x * factor + b <= location.y+10) {
                return true;
            }
        } else if (location.x >= startCoords.x-10 && location.x <= endCoords.x+10) {
            if (location.x * factor + b <= location.y+10 && location.x * factor + b >= location.y-10) {
                return true;
            }
        }
    } else {
        if (location.x <= startCoords.x+10 && location.x >= endCoords.x-10) {
            if (location.x * factor + b >= location.y-10 && location.x * factor + b <= location.y+10) {
                return true;
            }
        } else if (location.x >= startCoords.x-10 && location.x <= endCoords.x+10) {
            if (location.x * factor + b <= location.y+10 && location.x * factor + b >= location.y-10) {
                return true;
            }
        }
    }
    return false;
}

void saveMap() {
    nlohmann::json j;
    j["inner"]["lenght"] = innerMap.size();
    j["outer"]["lenght"] = outerMap.size();
    j["points"]["lenght"] = points.size();


    for (int i=0; i < innerMap.size(); i++) {
        j["inner"][std::to_string(i)]["x"] = innerMap.at(i).x;
        j["inner"][std::to_string(i)]["y"] = innerMap.at(i).y;
    }

    for (int i=0; i < outerMap.size(); i++) {
        j["outer"][std::to_string(i)]["x"] = outerMap.at(i).x;
        j["outer"][std::to_string(i)]["y"] = outerMap.at(i).y;
    }

    for (int i=0; i < points.size(); i++) {
        j["points"][std::to_string(i)]["start"]["x"] = points.at(i).at(0).x;
        j["points"][std::to_string(i)]["start"]["y"] = points.at(i).at(0).y;
        j["points"][std::to_string(i)]["end"]["x"] = points.at(i).at(1).x;
        j["points"][std::to_string(i)]["end"]["y"] = points.at(i).at(1).y;
    }
    j["spawn"]["lenght"] = spawnLocations.size();
    for (int i=0; i < spawnLocations.size(); i++) {
        j["spawn"][std::to_string(i)]["x"] = spawnLocations.at(i).x;
        j["spawn"][std::to_string(i)]["y"] = spawnLocations.at(i).y;
        j["spawn"][std::to_string(i)]["firstcheckpoint"] = firstCheckPoints.at(i);
        j["direction"][std::to_string(i)] = rotations.at(i);
    }


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
        point = false;
        selectpoint = false;
    } else if (IsKeyDown(KEY_P)) {
        inner = false;
        outer = true;
        spawn = false;
        point = false;
        selectpoint = false;
    } else if (IsKeyDown(KEY_Q)) {
        inner = false;
        outer = false;
        spawn = true;
        point = false;
        selectpoint = false;
    } else if (IsKeyDown(KEY_C)) {
        inner = false;
        outer = false;
        spawn = false;
        point = true;
        selectpoint = false;
    } else if (IsKeyDown(KEY_X)) {
        inner = false;
        outer = false;
        spawn = false;
        point = false;
        selectpoint = true;
    }
    if (inner) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 innerPosition = GetMousePosition();
            innerMap.push_back(innerPosition);
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && innerMap.size() != 0) {
            Vector2 innerPosition = GetMousePosition();
            innerMap.pop_back();
        }
    } else if (outer) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 outerPosition = GetMousePosition();
            outerMap.push_back(outerPosition);
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && outerMap.size() != 0) {
            Vector2 outerPosition = GetMousePosition();
            outerMap.pop_back();
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
        if (IsKeyPressed(KEY_LEFT_SHIFT)) {
            spawnLocations.push_back(spawnLocation);
            rotations.push_back(rotation);
        }
    } else if (point) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 innerPosition = GetMousePosition();
            points2.push_back(innerPosition);
            if (points2.size() == 2) {
                points.push_back(points2);
                points2.pop_back();
                points2.pop_back();
                pointcolor.push_back(0);
            }
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && points.size() != 0) {
            Vector2 innerPosition = GetMousePosition();
            // if (points)
            points.pop_back();
            pointcolor.pop_back();
            if (points2.size() != 0) {
                points2.pop_back();
            }
        }
    } else if (selectpoint) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 innerPosition = GetMousePosition();
            
            for (int i=0; i < points.size(); i++) {
                if (clickOnLine(innerPosition, i)) {
                    for (int j=0; j < pointcolor.size(); j++) {
                        pointcolor.at(j) = 0;
                    }
                    pointcolor.at(i) = 1;
                    firstCheckPoints.push_back(i);
                }
            }
        } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            for (int j=0; j < pointcolor.size(); j++) {
                pointcolor.at(j) = 0;
                firstCheckPoints.pop_back();
            }
        }
    }

    DrawCircle(spawnLocation.x, spawnLocation.y, 4, RED);
    Rectangle rectangle = {spawnLocation.x, spawnLocation.y, 10, 20};
    DrawRectanglePro(rectangle, {5, 10}, rotation, WHITE);  

    BeginDrawing();
    ClearBackground(backgroundColor);
    for (int i=0; i < spawnLocations.size(); i++) {
        DrawCircle(spawnLocations.at(i).x, spawnLocations.at(i).y, 4, RED);
        Rectangle rectangle = {spawnLocations.at(i).x, spawnLocations.at(i).y, 10, 20};
        DrawRectanglePro(rectangle, {5, 10}, rotations.at(i), WHITE);  
    }
    
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

    if ( points.size() == 0) {

    } else {
        for (int i=0; i < points.size(); i++) {
            if (pointcolor.at(i)) {
                DrawLineV(points.at(i).at(0), points.at(i).at(1), BLUE);
            } else {
                DrawLineV(points.at(i).at(0), points.at(i).at(1), YELLOW);
            }
            for (int j=0; j < firstCheckPoints.size(); j++) {
                if (firstCheckPoints.at(j) == i) {
                    DrawLineV(points.at(i).at(0), points.at(i).at(1), ORANGE);
                }
            }
            if (pointcolor.at(i)) {
                DrawLineV(points.at(i).at(0), points.at(i).at(1), BLUE);
            }

        }
    }
    // for (int i=0; i < firstCheckPoints.size(); i++) { 
    //     std::cout << firstCheckPoints.at(i);
    // }
    // std::cout << std::endl;
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