#include <raylib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "drawButtons.h"

class Drawer {
    public:
        Drawer();
        bool clickOnLine(Vector2 location, int i);
        void saveMap();
        void Render();
        void Start();
        void Update(double deltaTime);
        void run();
        void calcInnerWall(Vector2 firstPoint, Vector2 secondPoint);

    const int screenWidth = 1980;
    const int screenHeight = 1024;
    double rotation = 0;

    bool inner, outer, spawn, point, selectpoint;

    std::vector<bool> pointcolor;
    std::vector<double> rotations;
    std::vector<int> firstCheckPoints;
    std::vector<Vector2> spawnLocations;
    std::vector<Vector2> bestRoute;
    std::vector<Vector2> innerMap, outerMap, points2;
    std::vector<std::vector<Vector2>> points;
    Vector2 spawnLocation, angle;
    DrawMenu menu;
};

Drawer::Drawer() {
    float screenWidthf, screenHeightf;
    screenWidthf = float(screenWidth);
    screenHeightf = float(screenHeight);
}

bool Drawer::clickOnLine(Vector2 location, int i) {
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

void Drawer::saveMap() {
    nlohmann::json j;
    j["inner"]["lenght"] = innerMap.size();
    j["outer"]["lenght"] = outerMap.size();
    j["points"]["lenght"] = points.size();
    j["bestRoute"]["lenght"] = bestRoute.size();

    for (int i=0; i < bestRoute.size(); i++) {
        j["bestRoute"][std::to_string(i)]["x"] = bestRoute.at(i).x;
        j["bestRoute"][std::to_string(i)]["y"] = bestRoute.at(i).y;
    }

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
    testfile.open ("maps/example.json");
    testfile << j;
    testfile.close();
}

void Drawer::Render() {
    const Color backgroundColor = BLACK;

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

    for (int i=0; i < bestRoute.size(); i++) {
        if (i == bestRoute.size()-1) {
            DrawLineV(bestRoute.at(i), bestRoute.at(0), YELLOW);
        } else {
            DrawLineV(bestRoute.at(i), bestRoute.at(i+1), YELLOW);
        }
        DrawCircleV(bestRoute.at(i), 10, RED);
    }
    menu.Draw();

    DrawFPS(10,10);
    EndDrawing();
}

void Drawer::Start() {
    inner = true;
    outer = false;
}

void Drawer::Update(double deltaTime) {
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

    if (IsKeyDown(KEY_ENTER)) {
        saveMap();
    }

    if (IsKeyDown(KEY_G)) {
        bestRoute.clear();
        for (int i=0; i < innerMap.size(); i++) {
            if (i == innerMap.size()-1) {
                calcInnerWall(innerMap.at(i), innerMap.at(0));
            } else {
                calcInnerWall(innerMap.at(i), innerMap.at(i+1));
            }
        }
    }
}   

double lerps(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

Vector3 getIntersection(Vector2 A, Vector2 B, Vector2 C, Vector2 D) {
    double tTop = (D.x-C.x) * (A.y-C.y) - (D.y-C.y) * (A.x-C.x);
    double uTop = (C.y-A.y) * (A.x-B.x) - (C.x-A.x) * (A.y-B.y);
    double bottom = (D.y-C.y) * (B.x-A.x) - (D.x-C.x) * (B.y-A.y);
    double retVal[3];
    Vector3 test;
    test.x = 0;
    test.y = 0;
    test.z = 0;
    if (bottom != 0) {
        double t = tTop/bottom;
        double u = uTop/bottom;
        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            test.x = lerps(A.x, B.x, t);
            test.y = lerps(A.y, B.y, t);
            test.z = 5;
            std::cout << test.x << std::endl;
            return test;
        }
        std::cout << "ja " << std::endl;
    }
    std::cout << bottom << std::endl;
    return test;
}

void Drawer::calcInnerWall(Vector2 firstPoint, Vector2 secondPoint) {
    std::vector<Vector2> points;
    double directionX, directionY, direction, b1, b2;
    directionX = secondPoint.x - firstPoint.x;
    directionY = secondPoint.y - firstPoint.y;
    double f = directionY/directionX;
    

    b1 = firstPoint.x - f * firstPoint.y;

    Vector2 top, bottom;
    top.y = 0;
    top.x = b1;

    bottom.y = screenHeight;
    bottom.x = b1 + f * screenHeight;
    
    for (int i=0; i < outerMap.size(); i++) {
        Vector3 t;
        if (i == outerMap.size()-1) {
            t = getIntersection(top, bottom, outerMap.at(i), outerMap.at(0));
        } else {
            t = getIntersection(top, bottom, outerMap.at(i), outerMap.at(i+1));
        }

        if (t.z == 5) {
            // std::cout << t.x << std::endl;
            points.push_back({t.x, t.y});
        }
    }
    if (points.size() > 0) {
        int closest = 0;
        double closestDistance = sqrt(pow(firstPoint.x - points.at(0).x, 2) + pow(firstPoint.y - points.at(0).y, 2));
        for (int i=0; i < points.size(); i++) {
            double distance = sqrt(pow(firstPoint.x - points.at(i).x, 2) + pow(firstPoint.y - points.at(i).y, 2));
            if (distance < closestDistance) {
                closestDistance = distance;
                closest = i;
            }
        }

        std::cout << points.at(closest).x << " " << points.at(closest).y << std::endl;
        bestRoute.push_back({(firstPoint.x+points.at(closest).x)/2, (firstPoint.y+points.at(closest).y)/2});
    }
    BeginDrawing();
    ClearBackground(BLACK);

    DrawLineV(bottom, top, PINK);
    DrawCircleV(firstPoint, 10, PINK);

    EndDrawing();
}

void Drawer::run() {
    InitWindow(screenWidth, screenHeight, "car");
    SetWindowState(FLAG_VSYNC_HINT);

    Start();
    while (!WindowShouldClose()){
        double deltaTime = GetFrameTime();
        Update(deltaTime);
        Render();
    }

    CloseWindow();
}