#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>
#include <time.h>
#include <cstdlib>

#include "ray2.h"
#include "k/nn.h"

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
        std::vector<int> neuroncounts = {8, 255, 122, 16, 4};
        GeneticNeuralNetwork network;
    private:
        GRays rays;
        void move(double deltaTime, int action);
        double friction = 20;
        double acceleration = 50;
        double speed = 0;
        double maxSpeed = 200;
        Vector2 position;
        const Vector2 size{10, 20};
        double direction = 0;
        double angle;
        Rectangle rectangle;
        bool action[4];
        std::vector<Vector2> polygon, wallVec, outerWallVec;
        int currentPoint = 0;
        std::vector<std::vector<Vector2>> points;
        Vector2 previousPosition;
        double timeSinceLastPoint = 0;
        double epsilon;
};

GCar::GCar(GameMapE2 map, double newDirection, Vector2 newPosition) {
    network = GeneticNeuralNetwork({16, 16, 8, 6, 4});
    epsilon = 1;
    timeSinceLastPoint = 0;
    alive = true;
    currentPoints = 0;
    rays.setWallVec();
    direction = newDirection;
    angle = (direction / -(180/PI));
    speed = 0;
    position = newPosition;
    previousPosition = position;
}

GCar::~GCar() {

}

void GCar::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;
    speed = 0;
    position = newPosition;
    previousPosition = position;
    direction = newDirection;
    angle = (direction / -(180/PI));
    timeSinceLastPoint = 0;
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
    float x, y, y2,x2,x3,y3,x4,y4;
    double rad = hypot(size.x,size.y)/2;
    double alpha = atan2(size.x, size.y);

    x = position.x - sin(angle - alpha) * rad;
    y = position.y - cos(angle - alpha) * rad;

    x2 = position.x - sin(angle + alpha) * rad;
    y2 = position.y - cos(angle + alpha) * rad;

    x3 = position.x - sin(PI + angle-alpha) * rad;
    y3 = position.y - cos(PI + angle-alpha) * rad;

    x4 = position.x - sin(PI + angle + alpha) * rad;
    y4 = position.y - cos(PI + angle + alpha) * rad;

    polygon.push_back({x,y});
    polygon.push_back({x2,y2});
    polygon.push_back({x3,y3});
    polygon.push_back({x4,y4});
}

void GCar::draw(bool best) {
    Rectangle rectangle = {position.x, position.y, size.x, size.y};
    if (alive) {
        DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);  
    } else {
        DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, RED);
    }
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
    switch (action) {
        case 0:
            angle -= 3 * deltaTime;
            direction += (3 * (180/M_PI)) * deltaTime;
            break;
        case 1:
            angle += 3 * deltaTime;
            direction -= (3 * (180/M_PI)) * deltaTime;
            break;
        case 2:
            speed += acceleration * deltaTime;
            break;
        case 3:
            speed -= acceleration * deltaTime;
            break;
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

    position.x -= sin(angle) * speed * deltaTime;
    position.y -= cos(angle) * speed * deltaTime;
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
    // for (int i=0; i < map->wallVectorVec.size(); i++) {
    //     Vector4 test = rays.getIntersection(previousPosition, position, map->wallVectorVec[i], map->wallVectorVec[0]);
    //     if (test.w == 5) {
    //         return true;
    //     }
    // }

    for (int i=0; i < map->wallVectorVec.size(); i++) {
        if (polyIntersect(polygon, {map->wallVectorVec.at(i), map->wallVectorVec.at((i+1)%map->wallVectorVec.size())})) {
            return true;
        }
    }
    for (int i=0; i < map->outerWall.size(); i++) {
        if (polyIntersect(polygon, {map->outerWall.at(i), map->outerWall.at((i+1)%map->outerWall.size())})) {
            return true;
        }
    }

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
        return true;
    }

    return false;
}

void GCar::update(double deltaTime, GameMapE2* map) {
    if (alive) {
        rays.update(&position.x, &position.y, direction ,map);
        
        std::vector<Vector3> offsetVec = rays.hitCoordVec3;
        std::vector<double> offsets;
        for (int i=0; i < offsetVec.size(); i++) {
            if (offsetVec.at(i).z == 0) {
                offsets.push_back(0);
            } else {
                offsets.push_back(1 - offsetVec.at(i).z);
            }
        }
        std::vector<double> outputs;
        outputs = network.feedforward(offsets, network);
        outputsbool.clear();

        for (int i=0; i < 4; i++) {
            outputsbool.push_back(outputs[i]);
        }
        bool test = checkPointCollision(map);
        int bestindex = 0;
        if (checkPointCollision(map)) {
            collectedPoints++;
            currentPoints++;
            timeSinceLastPoint = 0;
        }
        timeSinceLastPoint += deltaTime;
        if (timeSinceLastPoint > 20) {
            alive = false;
        }

        // int highest = 0;
        // for (int i=0; i < outputs.size(); i++) {
        //     if (outputs.at(i) >= outputs.at(highest)) {
        //         highest = i;
        //     }
        // }
        // std::vector<double> actions2 = neuralNetwork.feedForward(offsets);
        // actions.clear();
        // for (int i=0; i < actions2.size(); i++) {
        //     if (actions2.at(i) > actions2.at(highest)) {
        //         highest = i;
        //     }
        // }
        // for (int i=0; i < actions2.size(); i++) {
        //     if (i == highest) {
        //         actions.push_back(1);
        //     } else {
        //         actions.push_back(0);
        //     }
        // }
        std::vector<double> actions2 = network.feedforward(offsets, network);
        int highest = 0;
        // actions.clear();
        for (int i=0; i < actions2.size(); i++) {
            if (actions2.at(i) > actions2.at(highest)) {
                highest = i;
            }
        }

        move(deltaTime, highest);
        rays.update(&position.x, &position.y, direction ,map);

        createPolygon();
        if(checkCollision(map)) {
            alive = false;
        } 
    }
}

std::vector<std::vector<double>>* GCar::returnPreviousStates() {
    std::vector<std::vector<double>>* previousStatesP = new std::vector<std::vector<double>>(previousStates);
    return previousStatesP;
}
