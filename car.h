#include <cmath>
#include <vector>

#include "ray.h"

class Car {
    public:
        Car(Vector2 newPosition, bool control);
        void update(double deltaTime);
        double accelerate(double dTime, bool forward);
        void castRay();
        void controls();
        void draw();

    private:
        Rays rays;
        void move(double deltaTime);
        double friction = 0.5;
        double acceleration = 2;
        double speed = 0;
        double maxSpeed = 5;
        Vector2 position;
        const Vector2 size{20, 40};
        double direction = 0;
        double angle;
        Rectangle rectangle;
        bool controlType;
        bool action[4];

};

Car::Car(Vector2 newPosition, bool control) {
    position = newPosition;
    controlType = control;
    
}

void Car::draw() {
    Rectangle rectangle = {position.x-size.x/2, position.y-size.y/2, size.x, size.y};
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
    } else {
        speed += friction * deltaTime;
    }

    // if (std::abs(speed) < friction*deltaTime) {
    //     speed = 0;
    // }
    // direction = (angle * (180/M_PI));
    
    if (speed != 0) {
        int flip;
        if (speed > 0) {
            flip = 1;
        } else {
            flip = -1;
        }
        if (action[2]) {
            angle -= 2 * deltaTime * flip;
            direction += (2 * (180/M_PI)) * deltaTime * flip;
        }
        if (action[3]) {
            angle += 2 * deltaTime * flip;
            direction -= (2 * (180/M_PI)) * deltaTime * flip;
        }
    }
    
    
    
    position.x -= sin(angle) * speed;
    position.y -= cos(angle) * speed;
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

void Car::update(double deltaTime) {
    rays.update({position.x-size.x/2, position.y-size.y/2}, angle);
    move(deltaTime);
}