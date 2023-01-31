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
        GCar(GameMapE2 newMap = GameMapE2(), double newDirection = 0, Vector2 newPosition = {0,0}, std::string newmaplocation = "maps/example.json", std::vector<int> newNNBlueprint = {8, 12, 12, 6, 4}, int rayAmount = 8, int rayLenght = 200);
        ~GCar();
        void update(double deltaTime);
        void draw(bool best);
        void createPolygon();
        bool checkCollision();
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);
        void setSpawn(Vector2 spawn, double newDirection);

        bool alive;
        int collectedPoints;

        std::vector<int> outputsbool;
        std::vector<int> neuroncounts;
        std::vector<double> previousState, previousState1, previousState2, previousState3, previousState4;

        GeneticNeuralNetwork network;
    private:
        void checkPointCollision();
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
        std::string maplocation;

        Vector2 position;
        Vector2 previousPosition;
        Rectangle rectangle;
        GRays rays;
        GameMapE2 *map;
};

GCar::GCar(GameMapE2 newMap, double newDirection, Vector2 newPosition, std::string newmaplocation, std::vector<int> newNNBlueprint, int rayAmount , int rayLenght) {
    network = GeneticNeuralNetwork(newNNBlueprint);
    neuroncounts = newNNBlueprint;
    map = new GameMapE2(newMap);
    rays = GRays(rayAmount, rayLenght);

    alive = true;
    maplocation = newmaplocation;

    std::ifstream f(maplocation);
    nlohmann::json mapData = nlohmann::json::parse(f); 
    f.close();

    speed = 0;
    collectedPoints = 0;
    currentPoint = mapData["spawn"][std::to_string(0)]["firstcheckpoint"].get<float>();
    timeSinceLastPoint = 0;
    
    position = newPosition;
    direction = newDirection;
    previousPosition = position;
    angle = (direction / -(180/PI));

    rays.setMap(*map);
}

GCar::~GCar() {
}

void GCar::setSpawn(Vector2 spawn, double newDirection) {
    position = spawn;
    direction = newDirection;
    angle = (direction / -(180/PI));
}


void GCar::createPolygon() { // creates a polygon using the position, rotation and size of the car
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
            rays.draw();
            DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, PINK);
        } else {
            DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);
        }
    } else {
        DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, RED);
    }
}

// changes speed and rotation/direction of the car by given input vector wih ints between 0 and 1;
void GCar::move(double deltaTime, std::vector<int> action) {
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

// checks if two polygons intersect
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

bool GCar::checkCollision() { // checks if the car collides with the wall by ussing polyintersect and the polygon of the car 
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

void GCar::checkPointCollision() { // check if car collides with the current target checkpoint
    if (polyIntersect(polygon, {map->points.at(currentPoint).at(0), map->points.at(currentPoint).at(1)})) {
        if (currentPoint == map->points.size()-1) {
            currentPoint = 0;
        } else {
            currentPoint++;
        }
        collectedPoints++;
        timeSinceLastPoint = 0;
    }
}

void GCar::update(double deltaTime) { // updates the location of the car and updates the rays
    if (alive) {
        rays.update(&position.x, &position.y, angle);
        
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
        outputs = network.feedForward(offsets);
        
        std::vector<int> outputsbool;

        for (int i=0; i < 4; i++) { // translate the network output from doubles to booleans/int wich are 0 or 1
            if (outputs.at(i) >= 0.5) {
                outputsbool.push_back(1);
            } else {
                outputsbool.push_back(0);
            }
        }

        timeSinceLastPoint += deltaTime;
        checkPointCollision(); // checks if the car collided with the current checkpoint it needs to collide with

        move(deltaTime, outputsbool);
        rays.update(&position.x, &position.y, angle);
    
        createPolygon();
        if(checkCollision()) { // checks if the car collided with the wall and sets the variable alive to false if it hit a wall
            alive = false;
        } else if (timeSinceLastPoint > 6) { // if the car hasn't hit an checkpoint for more than 6 seconds set alive to false
            alive = false;
        }
    }
}