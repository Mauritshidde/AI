#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>

#include "ray.h"
#include "Qlearning.h"
// #include "DeepQLearning.h"
// #include "Qnn.h"
// #include "nnLevel2.h"

class Car {
    public:
        Car(GameMapE* map, double newDirection, Vector2 newPosition);
        ~Car();
        void update(double deltaTime, GameMapE* map);
        double accelerate(double dTime, bool forward);
        void castRay();
        void controls();
        void draw(bool best);
        void createPolygon();
        bool checkCollision(GameMapE* map);
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);
        bool checkPointCollision(GameMapE* map);
        void restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon);
        void setSpawn(Vector2 spawn, double newDirection);

        std::vector<std::vector<double>> *returnPreviousStates();
        int collectedPoints = 0;
        int currentPoints;
        bool alive;
        std::vector<int> outputsbool;
        std::vector<double> previousState, previousState1, previousState2, previousState3, previousState4;
        std::vector<std::vector<double>> previousStates;
        Qlearning Qtable;
        // DeepQLearning DeepQnn;
        std::vector<int> neuroncounts = {8, 6, 6, 6, 4};
    private:
        // GameMapE* map;
        // Vector2* positionN = new Vector2();
        Rays rays;
        void move(double deltaTime, int action);
        void move2(double deltaTime, std::vector<double> actions, std::vector<double> offsets, GameMapE* map, double newEpsilon);
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

Car::Car(GameMapE* map, double newDirection, Vector2 newPosition) {
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

Car::~Car() {

}

void Car::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
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

void Car::setSpawn(Vector2 spawn, double newDirection) {
    position = spawn;
    direction = newDirection;
    angle = (direction / -(180/PI));
    previousStates.clear();
}


void Car::createPolygon() {
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

void Car::draw(bool best) {
    Rectangle rectangle = {position.x, position.y, size.x, size.y};
    DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);  
    rays.draw();
}

void Car::controls() {
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

void Car::move(double deltaTime, int action) {
    if (IsKeyDown(KEY_D)) {
        action = 0;
    }
    if (IsKeyDown(KEY_A)) {
        action = 1;
    }
    if (action == 2){
        speed += acceleration * deltaTime;
    } 

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

    // if (std::abs(speed) < friction*deltaTime) {
    //     speed = 0;
    // }
    // direction = (angle * (180/M_PI));
    
    // if (speed != 0) {
    // int flip;
    // if (speed > 0) {
    //     flip = 1;
    // } else {
    //     flip = -1;
    // }
    if (action == 0) {
        angle -= 3 * deltaTime;
        direction += (3 * (180/M_PI)) * deltaTime;
    }
    if (action == 1) {
        angle += 3 * deltaTime;
        direction -= (3 * (180/M_PI)) * deltaTime;
    }
    // }
    
    position.x -= sin(angle) * speed * deltaTime;
    position.y -= cos(angle) * speed * deltaTime;
    speed = maxSpeed;
}

std::vector<double> getAction(double x, double y,double z,double w) {
    return {x,y,z,w};
}

double Car::accelerate(double dTime, bool forward) {
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

bool Car::polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2) {
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

bool Car::checkCollision(GameMapE* map) {
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

bool Car::checkPointCollision(GameMapE* map) {
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

void Car::update(double deltaTime, GameMapE* map) {
    if (alive) {
        float* x = new float(position.x);
        float* y = new float(position.y);
        rays.update(x, y, angle, map);
        delete x;
        delete y;
        x = NULL;
        y = NULL;
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
        
        if (checkPointCollision(map)) {
            timeSinceLastPoint = 0;
            currentPoints++;
        }

        timeSinceLastPoint += deltaTime;
        if (timeSinceLastPoint >= 20) {
            alive = false;
            timeSinceLastPoint = 0;
        } 
        std::vector<double>* offsettsp = new std::vector<double>(offsets);

        int action = Qtable.makeDecision(&offsets);
        move(deltaTime, action);
        std::vector<Vector3> offsetVec2 = rays.hitCoordVec3;
        // int offsets[offsetVec.size()];
        std::vector<double> offsets4;
        for (int i=0; i < offsetVec2.size(); i++) {
            if (offsetVec2.at(i).z == 0) {
                // offsets[i] = 0;
                offsets4.push_back(0);
            } else {
                // offsets[i] = 1 - offsetVec.at(i).z;
                offsets4.push_back(1 - offsetVec2.at(i).z);
            }
        }
        previousStates.push_back(offsets4);
        
        // move(deltaTime, action);
        createPolygon();
        if(checkCollision(map)) {
            alive = false;
        } 
        // std::cout<<position.x<<"  "<<previousPosition.x<<"\n";
        previousPosition = position;

        float* x2 = new float(position.x);
        float* y2 = new float(position.y);
        rays.update(x2, y2, angle, map);
        
        // x2 = NULL;
        // y2 = NULL;
        // std::cout << "ja " << "kaas2" <<  "nee" << std::endl;
        delete x2;
        delete y2;
        x2 = NULL;
        y2 = NULL;
        // std::cout << "ja " <<  "nee" << std::endl;
        Qtable.Reward(true, &offsets);
        

    } 
    else {
        // neuralNetwork = neuralNetworkUpdate2;
        std::vector<Vector3> offsetVec = rays.hitCoordVec3;
        std::vector<double> offsets;
        for (int i=0; i < offsetVec.size(); i++) {
            if (offsetVec.at(i).z == 0) {
                offsets.push_back(0);
            } else {
                offsets.push_back(1 - offsetVec.at(i).z);
            }
        }
        int action = Qtable.makeDecision(&offsets);

        Qtable.Reward(false, &offsets);
    }
    // map = NULL;
    // delete map;
}

std::vector<std::vector<double>>* Car::returnPreviousStates() {
    std::vector<std::vector<double>>* previousStatesP = new std::vector<std::vector<double>>(previousStates);
    return previousStatesP;
}
