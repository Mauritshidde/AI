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
        GCar(GameMapE2 newMap = GameMapE2(), double newDirection = 0, Vector2 newPosition = {0,0}, std::vector<int> newNNBlueprint = {16, 6, 4});
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
        void move(double deltaTime, int action);
        
        const double friction = 20;
        const double acceleration = 50;
        const double maxSpeed = 200;
        const Vector2 size{10, 20};
        
        int currentPoint;
        double speed;
        double direction;
        double angle;
        double epsilon;
        double timeSinceLastPoint;

        std::vector<std::vector<Vector2>> points;
        std::vector<Vector2> polygon, wallVec, outerWallVec;
        
        Vector2 position;
        Vector2 previousPosition;
        Rectangle rectangle;
        GRays rays;
        GameMapE2 *map;
};

GCar::GCar(GameMapE2 newMap, double newDirection, Vector2 newPosition, std::vector<int> newNNBlueprint) {
    network = GeneticNeuralNetwork(newNNBlueprint);
    neuroncounts = newNNBlueprint;
    map = new GameMapE2(newMap);
    rays = GRays(16, 100);

    alive = true;

    speed = 0;
    epsilon = 1;
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
    delete map;
}

void GCar::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;
    
    speed = 0;
    timeSinceLastPoint = 0;
    currentPoints = 0;
    
    epsilon = newEpsilon;
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
    } else {
        DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, RED);
    }
    rays.draw();
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
        return true;
    }

    return false;
}

void GCar::update(double deltaTime) {
    if (alive) {
        rays.update(&position.x, &position.y, direction);
        
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
        bool test = checkPointCollision();
        int bestindex = 0;
        if (checkPointCollision()) {
            collectedPoints++;
            currentPoints++;
            timeSinceLastPoint = 0;
        }
        timeSinceLastPoint += deltaTime;
        if (timeSinceLastPoint > 20) {
            alive = false;
        }

        std::vector<double> actions2 = network.feedforward(offsets, network);
        int highest = 0;
        for (int i=0; i < actions2.size(); i++) {
            if (actions2.at(i) > actions2.at(highest)) {
                highest = i;
            }
        }

        move(deltaTime, highest);
        rays.update(&position.x, &position.y, direction);

        createPolygon();
        if(checkCollision()) {
            alive = false;
        } 
    }
}