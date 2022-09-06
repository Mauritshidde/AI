#include <raylib.h>
#include <iostream>
#include <cmath>


const int screenWidth = 1400;
const int screenHeight = 900;

bool server = false;

// class Maze {
// public:    
//     Maze(int row, int column);
//     void setRows(int row) { rows= row; } 
//     void setColumns(int column) { columns = column; }
//     void cellCounter() { cellAmount = rows * columns; }
//     void mazeCorner() { cornerCoordVec = {rows-1, columns-1};}
//     void mazeDataStructure();
//     void getCoordinateVec();
//     void mazeGen(int x, int y);
//     void printMaze();
//     std::vector<std::vector<int>> calcPosibleRoutes(int x, int y);
// private:
//     int rows;
//     int columns;
//     int cellAmount;
//     int visitedcells;
//     bool placeDots = true;
//     std::vector<int> cornerCoordVec;
//     std::vector<std::vector<int>> posibleCoordinates;
//     std::vector<std::vector<std::vector<bool>>> mazeStructurePrint;
//     Stack stack;
// };

// Maze::Maze(int row, int column) {
//     Maze::setRows(row);
//     Maze::setColumns(column);
//     Maze::mazeCorner();
//     Maze::getCoordinateVec();
//     Maze::mazeDataStructure();
// }

class Car {
    public:
        Car();
        void Draw();
        double acceleration = 1;
        double speed = 0;
        double maxSpeed = 5;
        Vector2 position;
        const Vector2 size{20, 40};
        double direction = 0;
        double angle;
};

Car::Car() {

}

Car car;

void Car::Draw() {
    Rectangle rectangle = {position.x-size.x/2, position.y-size.y/2, size.x, size.y};
    // DrawRectangle(position.x-size.x/2, position.y-size.y/2, size.x, size.y, WHITE);
    // car.direction += 0.03 * (180/M_PI);
    // std::cout << car.direction << std::endl;
    DrawRectanglePro(rectangle, {size.x/2, size.y/2}, car.direction, WHITE); 
}
void Render() {
    const Color backgroundColor = BLACK;

    BeginDrawing();
    ClearBackground(backgroundColor);
    car.Draw();

    //vec2Begin = {screenWidth/2, 0}
    //vec2Eind = {11, 1}
    DrawLineEx({screenWidth, 50}, {11, 50}, 5, WHITE);
    DrawLineEx({screenWidth/2, 0}, {screenWidth/2, screenHeight}, 1, WHITE);
    
    EndDrawing();
}

void Start() {
    car.position = {screenWidth/2, screenHeight/2};
    car.speed = 0;
}

void Update(double deltaTime) {
    if (IsKeyDown(KEY_W)){
        car.speed += car.acceleration * deltaTime;
    } 
    if (IsKeyDown(KEY_S)){
        car.speed -= car.acceleration * deltaTime;
    }
    if (car.speed > car.maxSpeed) {
        car.speed = car.maxSpeed;
    }
    if (IsKeyDown(KEY_D)){
        car.angle -= 0.03 * deltaTime;
        car.direction += (0.03 * (180/M_PI)) * deltaTime;
    }
    if (IsKeyDown(KEY_A)){
        car.angle += 30 * deltaTime;
        car.direction -= (30 * (180/M_PI)) * deltaTime;
    }
    // this.x -= Math.sin(this.angle) * this.speed;
    // this.y -= Math.cos(this.angle) * this.speed;
    // car.position.y += car.speed * deltaTime;
    std::cout << car.direction << std::endl;
    std::cout << car.angle << std::endl;

    car.position.x -= sin(car.angle) * car.speed;
    car.position.y -= cos(car.angle) * car.speed;

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