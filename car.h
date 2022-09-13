#include <cmath>
#include <vector>

#include "ray.h"

class Car {
    public:
        Car(Vector2 newPosition, bool control, std::vector<Vector2> map);
        void update(double deltaTime);
        double accelerate(double dTime, bool forward);
        void castRay();
        void controls();
        void draw();
        void createPolygon();
        bool checkCollision();
        bool polyIntersect(std::vector<Vector2> poly1, std::vector<Vector2> poly2);

    private:
        Rays rays;
        bool alive;
        void move(double deltaTime);
        double friction = 10;
        double acceleration = 40;
        double speed = 0;
        double maxSpeed = 100;
        Vector2 position;
        const Vector2 size{20, 40};
        double direction = 0;
        double angle;
        Rectangle rectangle;
        bool controlType;
        bool action[4];
        std::vector<Vector2> polygon, wallVec;
        


};

Car::Car(Vector2 newPosition, bool control, std::vector<Vector2> map) {
    position = newPosition;
    controlType = control;
    alive = true;
    wallVec = map;
    rays.setWallVec(map);
}

void Car::createPolygon() {
    polygon = {};
    polygon.push_back({position.x, position.y});
    polygon.push_back({position.x-size.x, position.y});
    polygon.push_back({position.x-size.x, position.y-size.y});
    polygon.push_back({position.x, position.y-size.y});
    // std::cout << points.at(0).x << "x " << points.at(1).x << "x " << points.at(2).x << "x " << points.at(3).x << std::endl;
    // std::cout << points.at(0).y << "y " << points.at(1).y << "y " << points.at(2).y << "y " << points.at(3).y << std::endl;
}

void Car::draw() {
    Rectangle rectangle = {position.x-size.x/2, position.y-size.y/2, size.x, size.y};
    createPolygon();
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

void Car::move(double deltaTime) {
    action[0] = 0;
    action[1] = 0;
    action[2] = 0;
    action[3] = 0;
    if (controlType) {
        controls();
    } else {

    }

    if (action[0]){
        speed += acceleration * deltaTime;
    } 
    if (action[1]){
        speed -= acceleration * deltaTime;
    }
    if (speed > maxSpeed) {
        speed = maxSpeed;
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
    if (action[2]) {
        angle -= 2 * deltaTime;
        direction += (2 * (180/M_PI)) * deltaTime;
    }
    if (action[3]) {
        angle += 2 * deltaTime;
        direction -= (2 * (180/M_PI)) * deltaTime;
    }
    // }
    
    
    
    position.x -= sin(angle) * speed * deltaTime;
    position.y -= cos(angle) * speed * deltaTime;
}

double Car::accelerate(double dTime, bool forward) {
    if (forward) {
        speed += acceleration * dTime;
    } else {
        speed -= acceleration * dTime;
    }
    if (speed > maxSpeed) {
        speed = maxSpeed;
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
    for (int i=0; i < wallVec.size(); i++) {
        // std::cout << wallVec.at(0).x;
        if (polyIntersect(polygon, {wallVec.at(i), wallVec.at((i+1)%wallVec.size())})) {
            return true;
        }
    }
    return false;
}

void Car::update(double deltaTime) {
    if (alive) {
        move(deltaTime);
        rays.update({position.x-size.x/2, position.y-size.y/2}, angle);
        createPolygon();
        if(checkCollision()) {
            alive = false;
        } 
    }
}
