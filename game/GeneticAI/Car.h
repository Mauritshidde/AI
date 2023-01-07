#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>
#include <time.h>
#include <cstdlib>

#include "ray2.h"
#include "../networkcode/GeneticAI/nn.h"

class GCar {
    public:
        GCar(GameMapE2 newMap = GameMapE2(), double newDirection = 0, Vector2 newPosition = {0,0}, std::vector<int> newNNBlueprint = {4, 6, 6, 8}, int rayAmount = 8, int rayLenght = 200);
        ~GCar();
        void update(double deltaTime);
        double accelerate(double dTime, bool forward);
        void castRay();
        void draw(bool best);
        void createPolygon();
        bool checkCollision();
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);
        bool checkPointCollision();
        void restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon);
        void setSpawn(Vector2 spawn, double newDirection);

        bool alive;
        int currentPoints;
        int collectedPoints = 0;

        std::vector<int> outputsbool;
        std::vector<int> neuroncounts;
        std::vector<double> previousState, previousState1, previousState2, previousState3, previousState4;

        GeneticNeuralNetwork network;
    private:
        void move(double deltaTime, std::vector<int> action);
        
        const double friction = 20;
        const double acceleration = 50;
        const double maxSpeed = 200;
        const Vector2 size{10, 20};
        
        int currentPoint;
        double speed;
        double direction;
        double angle;
        double timeSinceLastPoint;

        std::vector<std::vector<Vector2>> points;
        std::vector<Vector2> polygon, wallVec, outerWallVec;
        
        Vector2 position;
        Vector2 previousPosition;
        Rectangle rectangle;
        GRays rays;
        GameMapE2 *map;
};

GCar::GCar(GameMapE2 newMap, double newDirection, Vector2 newPosition, std::vector<int> newNNBlueprint, int rayAmount , int rayLenght) {
    network = GeneticNeuralNetwork(newNNBlueprint);
    neuroncounts = newNNBlueprint;
    map = new GameMapE2(newMap);
    rays = GRays(rayAmount, rayLenght);

    alive = true;

    speed = 0;
    currentPoint = 0;
    currentPoints = 0;
    timeSinceLastPoint = 0;
    
    position = newPosition;
    direction = newDirection;
    previousPosition = position;
    angle = (direction / -(180/PI));

    rays.setMap(*map);
}

GCar::~GCar() {
    // delete map;
}

void GCar::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;
    
    speed = 0;
    timeSinceLastPoint = 0;
    currentPoints = 0;
    
    position = newPosition;
    direction = newDirection;
    previousPosition = position;
    currentPoint = firstcheckpoint;
    angle = (direction / -(180/PI));
}

void GCar::setSpawn(Vector2 spawn, double newDirection) {
    position = spawn;
    direction = newDirection;
    angle = (direction / -(180/PI));
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
        if (best) { 
            DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, PINK);
        } else {
            DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);
        }
        // rays.draw();
    } else {
        DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, RED);
    }
}

void GCar::move(double deltaTime, std::vector<int> action) {
    // switch (action) {
    //     case 0:
    //         angle -= 3 * deltaTime;
    //         direction += (3 * (180/M_PI)) * deltaTime;
    //         break;
    //     case 1:
    //         angle += 3 * deltaTime;
    //         direction -= (3 * (180/M_PI)) * deltaTime;
    //         break;
    //     case 2:
    //         speed += acceleration * deltaTime;
    //         break;
    //     case 3:
    //         speed -= acceleration * deltaTime;
    //         break;
    // }

    if (action.at(0) == 1) {
        angle -= 3 * deltaTime;
        direction += (3 * (180/M_PI)) * deltaTime;
    }
    if (action.at(1) == 1) {
        angle += 3 * deltaTime;
        direction -= (3 * (180/M_PI)) * deltaTime;
    }
    if (action.at(2) == 1) {
        speed += acceleration * deltaTime;
    }
    if (action.at(3) == 1) {
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

bool GCar::checkCollision() {
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

bool GCar::checkPointCollision() {
    if (polyIntersect(polygon, {map->points.at(currentPoint).at(0), map->points.at(currentPoint).at(1)})) {
        if (currentPoint == map->points.size()-1) {
            currentPoint = 0;
        } else {
            currentPoint++;
        }
        collectedPoints++;
        timeSinceLastPoint = 0;
        return true;
    }

    return false;
}

void GCar::update(double deltaTime) {
    if (alive) {
        rays.update(&position.x, &position.y, angle);
        
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
        std::cout << outputs.size() << std::endl;
        // std::cout << outputs[0] << " " << outputs[1] << " " << outputs[2] << " " << outputs[3] << std::endl;
        
        std::vector<int> outputsbool;
        for (int i=0; i < 4; i++) {
            outputsbool.push_back(outputs[i]);
        }
        bool test = checkPointCollision();
        // if (collectedPoints != 0) {
        // std::cout << collectedPoints << std::endl;
        timeSinceLastPoint += deltaTime;
        // }
        move(deltaTime, outputsbool);
        rays.update(&position.x, &position.y, angle);
    
        createPolygon();
        if(checkCollision()) {
            alive = false;
        } else if (timeSinceLastPoint > 6) {
            alive = false;
        }
    }
}