#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>

#include "ray2.h"
// #include "Qlearning.h"
// #include "DeepQLearning.h"
// #include "Qnn.h"
#include "nn.h"

class GCar {
    public:
        GCar(GameMapE2 map = GameMapE2(), double newDirection = 0, Vector2 newPosition = {0,0});
        ~GCar();
        void update(double deltaTime, GameMapE2* map);
        double accelerate(double dTime, bool forward);
        void castRay();
        void controls();
        void draw(bool best);
        void createPolygon();
        bool checkCollision(GameMapE2* map);
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);
        bool checkPointCollision(GameMapE2* map);
        void restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon);
        void setSpawn(Vector2 spawn, double newDirection);

        std::vector<std::vector<double>> *returnPreviousStates();
        int collectedPoints = 0;
        int currentPoints;
        bool alive;
        std::vector<int> outputsbool;
        std::vector<double> previousState, previousState1, previousState2, previousState3, previousState4;
        std::vector<std::vector<double>> previousStates;
        // Qlearning Qtable;
        // DeepQLearning DeepQnn;
        std::vector<int> neuroncounts = {8, 255, 122, 16, 4};
        GeneticNeuralNetwork network = GeneticNeuralNetwork({8, 6, 6, 6, 4});
    private:
        // GameMapE2* map;
        // Vector2* positionN = new Vector2();
        GRays rays;
        void move(double deltaTime, int action);
        void move2(double deltaTime, std::vector<double> actions, std::vector<double> offsets, GameMapE2* map, double newEpsilon);
        double friction = 20;
        double acceleration = 50;
        double speed = 0;
        double maxSpeed = 200;
        Vector2 position;
        const Vector2 size{10, 20};
        double direction = 0;
        double angle;
        Rectangle rectangle;
        // bool controlType;
        bool action[4];
        std::vector<Vector2> polygon, wallVec, outerWallVec;
        // int wallArraySize;
        int currentPoint = 0;
        std::vector<std::vector<Vector2>> points;
        Vector2 previousPosition;
        double timeSinceLastPoint = 0;
        double epsilon;
};

GCar::GCar(GameMapE2 map, double newDirection, Vector2 newPosition) {
    // map = m;
    epsilon = 1;
    timeSinceLastPoint = 0;
    // controlType = 1;
    alive = true;
    currentPoints = 0;
    // wallVec = map->wallVectorVec;
    // outerWallVec = map->outerWall;
    rays.setWallVec();
    // wallArraySize = map->arraySize;
    direction = newDirection;
    angle = (direction / -(180/PI));
    // points = map->points;

    speed = 0;
    // acceleration = 50;
    // position = map->spawns.at(0);
    position = newPosition;
    // position = newSpawn;
    previousPosition = position;
    // map = NULL;
    // delete map;
}

GCar::~GCar() {
    // map = NULL;
    // delete map;
    // rays.~Rays();
}

void GCar::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;
    speed = 0;
    position = newPosition;
    previousPosition = position;
    direction = newDirection;
    angle = (direction / -(180/PI));
    timeSinceLastPoint = 0;
    // controlType = 1;
    currentPoint = firstcheckpoint;
    epsilon = newEpsilon;
    currentPoints = 0;
}

void GCar::setSpawn(Vector2 spawn, double newDirection) {
    position = spawn;
    direction = newDirection;
    angle = (direction / -(180/PI));

    previousStates.clear();
}


void GCar::createPolygon() {
    polygon = {};
    Vector2 polygonCenter = {position.x, position.y};
    // DrawCircle(int(polygonCenter.x), int(polygonCenter.y), 20, RED); 
    float x, y, y2,x2,x3,y3,x4,y4;
    double rad = hypot(size.x,size.y)/2;
    double alpha = atan2(size.x, size.y);
    // x = position.x - cos(angle-hypot(size.x,size.y)) * size.x;
    // y = position.x - sin(angle) * size.x;
    // x = (position.x * cos(angle) - position.y * sin(angle)) * position.x;
    // y = (position.x * sin(angle) - position.y * cos(angle)) * position.y;
    // x = x*cos(angle)-y*sin(angle);
    // y = y*sin(angle)+x*cos(angle);
    x = position.x - sin(angle - alpha) * rad;
    y = position.y - cos(angle - alpha) * rad;

    x2 = position.x - sin(angle + alpha) * rad;
    y2 = position.y - cos(angle + alpha) * rad;

    x3 = position.x - sin(PI + angle-alpha) * rad;
    y3 = position.y - cos(PI + angle-alpha) * rad;

    x4 = position.x - sin(PI + angle + alpha) * rad;
    y4 = position.y - cos(PI + angle + alpha) * rad;
    // x = polygonCenter.x + size.x/2 *sin(angle-alpha) - size.y/2 *cos(angle);
    // y = polygonCenter.x + size.x/2 *cos(angle-alpha) + size.y/2 *sin(angle);

    // x2 = polygonCenter.x - size.x/2 *sin(angle-alpha) - size.y/2 *cos(angle);
    // y2 = polygonCenter.x - size.x/2 *cos(angle-alpha) + size.y/2 *sin(angle);

    // x3 = polygonCenter.x - size.x/2 *sin(angle-alpha) + size.y/2 *cos(angle);
    // y3 = polygonCenter.x - size.x/2 *cos(angle-alpha) - size.y/2 *sin(angle);

    // x4 = polygonCenter.x + size.x/2 *sin(angle-alpha) + size.y/2 *cos(angle);
    // y4 = polygonCenter.x + size.x/2 *cos(angle-alpha) - size.y/2 *sin(angle);

    // std::cout << x << " " << y << " " << position.x << " " << position.y << std::endl;
    // x = position.x*sin(angle);
    // y = position.y*sin(angle);
    // std::cout<< x << " x " << position.x << std::endl;
    // std::cout<< y << " y " << position.y << std::endl;

    polygon.push_back({x,y});
    polygon.push_back({x2,y2});
    polygon.push_back({x3,y3});
    polygon.push_back({x4,y4});
    // DrawLineV(polygon.at(0), polygon.at(1), RED);
    // DrawLineV(polygon.at(1), polygon.at(2), RED);

    // DrawLineV(polygon.at(2), polygon.at(3), RED);
    // DrawLineV(polygon.at(3), polygon.at(0), RED);
    // std::cout << points.at(0).x << "x " << points.at(1).x << "x " << points.at(2).x << "x " << points.at(3).x << std::endl;
    // std::cout << points.at(0).y << "y " << points.at(1).y << "y " << points.at(2).y << "y " << points.at(3).y << std::endl;
}

void GCar::draw(bool best) {
    // if (best) {}
    Rectangle rectangle = {position.x, position.y, size.x, size.y};
    DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);  
    rays.draw();
}

void GCar::controls() {
    if (IsKeyDown(KEY_W)){
        action[0] = 1;
    } 
    if (IsKeyDown(KEY_S)){
        action[1] = 1;
    } 
    if (IsKeyDown(KEY_D)) {
        action[2] = 1;
    }
    if (IsKeyDown(KEY_A)) {
        action[3] = 1;
    }
}

void GCar::move(double deltaTime, int action) {
    // action[0] = outputsbool.at(0);
    // action[1] = outputsbool.at(1);
    // action[2] = outputsbool.at(2);
    // action[3] = outputsbool.at(3);
    // if (controlType) {
    //     controls();
    // } else {

    // }
    // if (IsKeyDown(KEY_W)){
    //     action[0] = 1;
    // } 
    // if (IsKeyDown(KEY_S)){
    //     action[1] = 1;
    // } 
    // action = 100;
    if (IsKeyDown(KEY_D)) {
        action = 0;
    }
    if (IsKeyDown(KEY_A)) {
        action = 1;
    }
    if (action == 2){
        speed += acceleration * deltaTime;
    } 
    // if (outputsbool.at(1) == 1 && speed > 0){
    //     speed -= acceleration * 10 * deltaTime;
    //     if (speed < 0) {
    //         speed = 0;
    //     }
    if (action == 3){
        speed -= acceleration * deltaTime;
    }
    if (speed > maxSpeed) {
        speed = maxSpeed;
    } else if (speed < -maxSpeed/2) {
        speed = -maxSpeed/2;
    }
    if (speed > 0) {
        speed -= friction * deltaTime;
    } else if (speed < 0) {
        speed += friction * deltaTime;
    }

    if (action == 0) {
        angle -= 3 * deltaTime;
        direction += (3 * (180/M_PI)) * deltaTime;
    }
    if (action == 1) {
        angle += 3 * deltaTime;
        direction -= (3 * (180/M_PI)) * deltaTime;
    }

    position.x -= sin(angle) * speed * deltaTime;
    position.y -= cos(angle) * speed * deltaTime;
    speed = maxSpeed;
}

double GCar::accelerate(double dTime, bool forward) {
    if (forward) {
        speed += acceleration * dTime;
    } else {
        speed -= acceleration * dTime;
    }
    if (speed > maxSpeed) {
        speed = maxSpeed;
    }if (speed < -maxSpeed/2) {
        speed = maxSpeed/2;
    }
    return speed;
}

bool GCar::polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2) {
    for (int i=0; i < poly1.size(); i++) {
        for (int j=0; j < poly2.size(); j++) {
            Vector4 check = rays.getIntersection(poly1.at(i), poly1.at((i+1)%poly1.size()), poly2.at(j), poly2.at((j+1)%poly2.size()));
            if (check.w == 5) {
                return true;
            }
        }
    }
    return false;
}

bool GCar::checkCollision(GameMapE2* map) {
    // if (rays.getIntersection(previousPosition, position)) {
    //     return true;
    // }
    for (int i=0; i < map->wallVectorVec.size(); i++) {
        // std::cout << wallVec.at(0).x;

        Vector4 test = rays.getIntersection(previousPosition, position, map->wallVectorVec[i], map->wallVectorVec[0]);
        if (test.w == 5) {
            return true;
        }

    }

    for (int i=0; i < map->wallVectorVec.size(); i++) {
        // std::cout << wallVec.at(0).x;

        if (polyIntersect(polygon, {map->wallVectorVec.at(i), map->wallVectorVec.at((i+1)%map->wallVectorVec.size())})) {
            return true;
        }
    }
    for (int i=0; i < map->outerWall.size(); i++) {
        // std::cout << wallVec.at(0).x;
        if (polyIntersect(polygon, {map->outerWall.at(i), map->outerWall.at((i+1)%map->outerWall.size())})) {
            return true;
        }
    }

    // map = NULL;
    // delete map;
    return false;
}

bool GCar::checkPointCollision(GameMapE2* map) {
    if (polyIntersect(polygon, {map->points.at(currentPoint).at(0), map->points.at(currentPoint).at(1)})) {
        if (currentPoint == map->points.size()-1) {
            currentPoint = 0;
        } else {
            currentPoint++;
        }
        collectedPoints++;
        // std::cout << collectedPoints << " " << timeSinceLastPoint << std::endl;
        return true;
    }

    // map = NULL;
    // delete map;
    return false;
}

void GCar::update(double deltaTime, GameMapE2* map) {
    if (alive) {
        rays.update(&position.x, &position.y, direction ,map);
        
        std::vector<Vector3> offsetVec = rays.hitCoordVec3;
        // int offsets[offsetVec.size()];
        std::vector<double> offsets;
        for (int i=0; i < offsetVec.size(); i++) {
            if (offsetVec.at(i).z == 0) {
                // offsets[i] = 0;
                offsets.push_back(0);
            } else {
                // offsets[i] = 1 - offsetVec.at(i).z;
                offsets.push_back(1 - offsetVec.at(i).z);
            }
        }
        std::vector<double> outputs;
        outputs = network.feedforward(offsets, network);
        // std::cout << outputs[0] << " " << outputs[1] << " " << outputs[2] << " " << outputs[3] << std::endl;
        
        outputsbool.clear();
        for (int i=0; i < 4; i++) {
            outputsbool.push_back(outputs[i]);
        }
        bool test = checkPointCollision(map);
        // if (collectedPoints != 0) {
        // std::cout << collectedPoints << std::endl;

        // }
        int bestindex = 0;
        for (int i=0; i < outputsbool.size(); i++) {
            if (outputsbool.at(i) == 1) {
                bestindex = i;
            }
        }

        move(deltaTime, bestindex);

        createPolygon();
        if(checkCollision(map)) {
            alive = false;
        } 
    } 
    else {
        // network = networkUpdate2;
    }
    // map = NULL;
    // delete map;
}

std::vector<std::vector<double>>* GCar::returnPreviousStates() {
    std::vector<std::vector<double>>* previousStatesP = new std::vector<std::vector<double>>(previousStates);
    return previousStatesP;
}
