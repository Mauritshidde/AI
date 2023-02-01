#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>

#include "ray.h"
#include "../networkcode/DeepNN/nn.h"

class Car {
    public:
        Car(Map* newMap, double newDirection, Vector2 newPosition, std::vector<int> newNNBlueprint = {8, 12, 12, 6, 4});
        ~Car();
        void update(double deltaTime, Vector2 *screen);
        double accelerate(double dTime, bool forward);
        void castRay();
        void draw(bool best);
        void createPolygon();
        bool checkCollision();
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);
        bool checkPointCollision();
        void restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon);

        int collectedPoints;
        int currentPoints;
        bool alive;

        std::vector<int> outputsbool;
        std::vector<int> neuroncounts = {18, 12, 12, 6, 4};

        NeuralNetwork neuralNetwork;
        Map *map;
    private:
        std::vector<double> move3(double deltaTime, std::vector<double> actions, std::vector<double> offsets, double newEpsilon);
        std::vector<double> move4(double deltaTime, std::vector<double> actions, std::vector<double> offsets, double newEpsilon);

        double friction, acceleration, speed, maxSpeed;
        double epsilon;
        double timeSinceLastPoint;
        double direction, angle;

        int currentPoint;
        
        Vector2 position, position2;
        Vector2 previousPosition;
        Vector2 size{10, 20};
        const Vector2 size2{10, 20};

        std::vector<Vector2> polygon, wallVec, outerWallVec;
        // std::vector<std::vector<Vector2>> points;

        Rays rays;
        Rectangle rectangle;
        NeuralNetwork neuralNetworkUpdate;
        NeuralNetwork neuralNetworkUpdate2;
};

Car::Car(Map* newMap, double newDirection, Vector2 newPosition, std::vector<int> newNNBlueprint) {
    map = newMap;
    neuralNetwork = NeuralNetwork(newNNBlueprint);
    neuralNetworkUpdate = neuralNetwork;
    neuralNetworkUpdate2 = neuralNetwork;

    alive = true;

    speed = 0;
    epsilon = 1;
    friction = 20;
    maxSpeed = 200;
    currentPoint = 0;
    acceleration = 50;
    currentPoints = 0;
    collectedPoints = 0;
    timeSinceLastPoint = 0;

    position = newPosition;
    position2 = position;
    direction = newDirection;
    previousPosition = position;
    angle = (direction / -(180/PI));

    position.x = (position2.x/1980)*GetScreenWidth();
    position.y = (position2.y/1024)*GetScreenHeight();
}

Car::~Car() {

}

void Car::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;

    speed = 0;
    currentPoints = 0;
    timeSinceLastPoint = 0;

    epsilon = newEpsilon;
    position = newPosition;
    position2 = position;
    direction = newDirection;
    previousPosition = position;
    currentPoint = firstcheckpoint;
    angle = (direction / -(180/PI));
    neuralNetworkUpdate = neuralNetwork;

    position.x = (position2.x/1980)*GetScreenWidth();
    position.y = (position2.y/1024)*GetScreenHeight();
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
    rectangle = {position.x, position.y, size.x, size.y};
    DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);  
    rays.draw();
}

std::vector<double> getAction(double x, double y,double z,double w) {
    return {x,y,z,w};
}

std::vector<double> Car::move3(double deltaTime, std::vector<double> actions, std::vector<double> offsets, double epsilon) {
    double random = rand() % 100;
    random = random/100;

    if (random <= epsilon) {
        int randval = rand() % 4;
        switch (randval) {
            case 0:
                actions = getAction(0,0,0,0);
                break;
            case 1:
                actions = getAction(1,0,0,0);
                break;
            case 2:
                actions = getAction(0,1,0,0);
                break;
            case 3:
                actions = getAction(0,0,1,0);
                break;
            case 4:
                actions = getAction(0,0,0,1);
                break;
            case 5:
                actions = getAction(0,0,1,0);
                break;
            case 6:
                actions = getAction(0,0,0,1);
                break;
            case 7:
                actions = getAction(0,0,1,0);
                break;
            case 8:
                actions = getAction(0,0,0,1);
                break;
            case 9:
                actions = getAction(0,0,1,0);
                break;
            case 10:
                actions = getAction(0,0,1,0);
                break;
            case 11:
                actions = getAction(0,0,1,0);
                break;
            case 12:
                actions = getAction(0,0,1,0);
                break;
        }
    } else {
        std::vector<double> actions2 = neuralNetwork.feedForward(offsets);
        int highest = 0;
        actions.clear();
        for (int i=0; i < actions2.size(); i++) {
            if (actions2.at(i) > actions2.at(highest)) {
                highest = i;
            }
        }
        for (int i=0; i < actions2.size(); i++) {
            if (i == highest) {
                actions.push_back(1);
            } else {
                actions.push_back(0);
            }
        }
    }

    if (actions.at(2) == 1) {
        speed += acceleration * deltaTime;
    } 

    if (actions.at(3) == 1) {
        speed -= acceleration * deltaTime;
    }

    if (actions.at(0) == 1) {
        angle -= 3 * deltaTime;
        direction += (3 * (180/M_PI)) * deltaTime;
    }
    if (actions.at(1) == 1) {
        angle += 3 * deltaTime;
        direction -= (3 * (180/M_PI)) * deltaTime;
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

    return actions;
}

std::vector<double> Car::move4(double deltaTime, std::vector<double> actions, std::vector<double> offsets, double epsilon) {
    double random = rand() % 100;
    random = random/100;

    if (random <= epsilon) {
        int randval = rand() % 4;
        switch (randval) {
            case 0:
                actions = getAction(0,0,0,0);
                break;
            case 1:
                actions = getAction(1,0,0,0);
                break;
            case 2:
                actions = getAction(0,1,0,0);
                break;
            case 3:
                actions = getAction(0,0,1,0);
                break;
        }
    } else {
        std::vector<double> actions2 = neuralNetwork.feedForward(offsets);
        int highest = 0;
        actions.clear();
        for (int i=0; i < actions2.size(); i++) {
            if (actions2.at(i) >= 0.5) {
                actions.push_back(1);
            } else {
                actions.push_back(0);
            }
        }
    }

    if (actions.at(0) == 1) {
        angle -= 3 * deltaTime;
        direction += (3 * (180/M_PI)) * deltaTime;
    }
    if (actions.at(1) == 1) {
        angle += 3 * deltaTime;
        direction -= (3 * (180/M_PI)) * deltaTime;
    }
    if (actions.at(2) == 1) {
        speed += acceleration * deltaTime;
    }
    if (actions.at(3) == 1) {
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

    position2.x -= sin(angle) * speed * deltaTime;
    position2.y -= cos(angle) * speed * deltaTime;
    position.x = (position2.x/1980)*GetScreenWidth();
    position.y = (position2.y/1024)*GetScreenHeight();

    return actions;
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

bool Car::checkCollision() {
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

bool Car::checkPointCollision() {
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

void Car::update(double deltaTime, Vector2 *screen) {
    size.x = (size2.x/1980)*screen->x;
    size.y = (size2.y/1024)*screen->y;
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

        std::vector<double>* offsettsp = new std::vector<double>(offsets);
        std::vector<double> actions = neuralNetwork.feedForward(offsets);
        
        actions = move4(deltaTime, actions, offsets, epsilon);

        int bestAction = 0;
        for (int i=0; i < actions.size(); i++) {
            if (actions.at(i) > actions.at(bestAction)) {
                bestAction = i;
            }
        }
        double reward = 1;
        if (checkPointCollision()) {
            timeSinceLastPoint = 0;
            neuralNetworkUpdate2 = neuralNetworkUpdate;
            reward = 10;
            currentPoints++;
        }
        timeSinceLastPoint += deltaTime;
        if (timeSinceLastPoint >= 20) {
            alive = false;
            timeSinceLastPoint = 0;
            reward = 0;
        } 

        std::vector<Vector3> offsetVec2 = rays.hitCoordVec3;
        std::vector<double> offsets4;
        for (int i=0; i < offsetVec2.size(); i++) {
            if (offsetVec2.at(i).z == 0) {
                offsets4.push_back(0);
            } else {
                offsets4.push_back(1 - offsetVec2.at(i).z);
            }
        }
        
        createPolygon();
        if(checkCollision()) {
            reward = -10;
            alive = false;
        } 
        previousPosition = position;

        std::vector<double> target;
        for (int i=0; i < actions.size(); i++) {
            if (i == bestAction) {
                target.push_back(1);
            } else {
                target.push_back(0);
            }
        }

        std::vector<double> target2;
        for (int i=0; i < actions.size(); i++) {
            if (i == bestAction) {
                target2.push_back(0);
            } else {
                target2.push_back(1);
            }
        }

        std::vector<double> *targetptr = new std::vector<double>(target);
        std::vector<double> *offsetsptr = new std::vector<double>(offsets);

        std::vector<double> *targetptr2 = new std::vector<double>(target2);

        neuralNetwork.backPropogation(targetptr2, offsetsptr);
        neuralNetworkUpdate2.backPropogation(targetptr, offsetsptr);
        
        delete targetptr;
        delete offsetsptr;
        delete targetptr2;

        float* x2 = new float(position.x);
        float* y2 = new float(position.y);
        rays.update(x2, y2, angle, map);
        
        delete x2;
        delete y2;
        x2 = NULL;
        y2 = NULL;
    } 
    else {
        neuralNetwork = neuralNetworkUpdate2;
    }
}
