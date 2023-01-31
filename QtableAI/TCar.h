#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>

#include "ray.h"
#include "../networkcode/Qtable/Qlearning.h"

class TCar {
    public:
        TCar(GameMap *newMap, double newDirection, Vector2 newPosition);
        ~TCar();
        void update(double deltaTime);
        double accelerate(double dTime, bool forward);
        void draw(bool best);
        void createPolygon();
        bool checkCollision();
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);
        bool checkPointCollision();
        void restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon);

        bool alive;
        int currentPoints;
        int collectedPoints;

        std::vector<int> outputsbool;
        Qlearning Qtable;
    private:
        void move(double deltaTime, int action);
        void move2(double deltaTime, std::vector<double> actions, std::vector<double> offsets, double newEpsilon);

        TRays rays = TRays(16, 200);
        GameMap *map;

        Rectangle rectangle;
        Vector2 position;
        std::vector<Vector2> polygon, wallVec, outerWallVec;
        std::vector<std::vector<Vector2>> points;
        Vector2 previousPosition;

        const Vector2 size{10, 20};
        const double friction = 20;
        const double acceleration = 50;
        const double maxSpeed = 200;

        double speed;
        double angle;
        double epsilon;
        double direction;
        int currentPoint;
        double timeSinceLastPoint;
};

TCar::TCar(GameMap *newMap, double newDirection, Vector2 newPosition) {
    map = newMap;

    alive = true;

    speed = 0;
    epsilon = 1;
    direction = 0;
    currentPoint = 0;
    currentPoints = 0;
    collectedPoints = 0;
    timeSinceLastPoint = 0;

    position = newPosition;
    direction = newDirection;
    angle = (direction / -(180/PI));
    previousPosition = position;
}

TCar::~TCar() {

}

void TCar::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;

    speed = 0;
    currentPoints = 0;
    timeSinceLastPoint = 0;

    epsilon = newEpsilon;
    position = newPosition;
    direction = newDirection;
    previousPosition = position;
    currentPoint = firstcheckpoint;
    angle = (direction / -(180/PI));
}

void TCar::createPolygon() {
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

void TCar::draw(bool best) {
    Rectangle rectangle = {position.x, position.y, size.x, size.y};
    DrawRectanglePro(rectangle, {size.x/2, size.y/2}, direction, WHITE);  
    rays.draw();
}

void TCar::move(double deltaTime, int action) {
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

double TCar::accelerate(double dTime, bool forward) {
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

bool TCar::polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2) {
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

bool TCar::checkCollision() {
    for (int i=0; i < map->wallVectorVec.size(); i++) {
        Vector4 test = rays.getIntersection(previousPosition, position, map->wallVectorVec[i], map->wallVectorVec[0]);
        if (test.w == 5) {
            return true;
        }

    }

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

bool TCar::checkPointCollision() {
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

void TCar::update(double deltaTime) {
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
        
        if (checkPointCollision()) {
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
            alive = false;
        } 
        previousPosition = position;

        float* x2 = new float(position.x);
        float* y2 = new float(position.y);
        rays.update(x2, y2, angle, map);
        
        delete x2;
        delete y2;
        x2 = NULL;
        y2 = NULL;
        Qtable.Reward(true, &offsets);
        

    } 
    else {
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
}