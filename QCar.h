#include <cmath>
#include <vector>
#include <iostream>
#include <ostream>

#include "ray.h"
// #include "Qlearning.h"
// #include "DeepQLearning.h"
// #include "Qnn.h"
#include "nnLevel2.h"

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
        // Qlearning Qtable;
        // DeepQLearning DeepQnn;
        std::vector<int> neuroncounts = {8, 255, 122, 16, 4};
        NeuralNetwork neuralNetwork = NeuralNetwork({8, 22, 16, 12, 8, 5, 4});
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
        bool controlType;
        bool action[4];
        std::vector<Vector2> polygon, wallVec, outerWallVec;
        int wallArraySize;
        int currentPoint = 0;
        std::vector<std::vector<Vector2>> points;
        Vector2 previousPosition;
        double timeSinceLastPoint = 0;
        double epsilon;
        NeuralNetwork neuralNetworkUpdate = NeuralNetwork({8, 22, 16, 12, 8, 5, 4});
        NeuralNetwork neuralNetworkUpdate2 = NeuralNetwork({8, 22, 16, 12, 8, 5, 4});
};

Car::Car(GameMapE* map, double newDirection, Vector2 newPosition) {
    // map = m;
    neuralNetworkUpdate = neuralNetwork;
    neuralNetworkUpdate2 = neuralNetwork;
    epsilon = 1;
    timeSinceLastPoint = 0;
    controlType = 1;
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

Car::~Car() {
    // map = NULL;
    // delete map;
    // rays.~Rays();
}

void Car::restartLocation(double newDirection, double firstcheckpoint, Vector2 newPosition, double newEpsilon) {
    alive = true;
    speed = 0;
    neuralNetworkUpdate = neuralNetworkUpdate;
    position = newPosition;
    previousPosition = position;
    direction = newDirection;
    angle = (direction / -(180/PI));
    timeSinceLastPoint = 0;
    controlType = 1;
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

void Car::draw(bool best) {
    // if (best) {}
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
void Car::move2(double deltaTime, std::vector<double> actions, std::vector<double> offsets, GameMapE* map, double epsilon) {
    // if (IsKeyDown(KEY_D)) {
    //     action = 0;
    // }
    
    // w a
    // wd 
    // w
    // s
    // d
    // a
    // sd
    // sa
    
    // double epsilon = 0.9;
    double random = rand() % 100;
    random = random/100;
    // epsilon = 0;
    // std::cout << epsilon << " " << random << std::endl;
    if (random <= epsilon) {
        // std::cout << "nee" <<std::endl;
        int randval = rand() % 15;
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
                actions = getAction(1,0,1,0);
                break;
            case 6:
                actions = getAction(1,0,0,1);
                break;
            case 7:
                actions = getAction(0,1,1,0);
                break;
            case 8:
                actions = getAction(0,1,0,1);
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
            case 13:
                actions = getAction(0,1,1,0);
                break;
            case 14:
                actions = getAction(1,0,1,0);
                break;
        }
    } else {
        actions = neuralNetwork.feedForward(offsets);
    }

    std::vector<double> target;
    double w,s,a,d;
    w = 0;
    s = 0;
    a = 0;
    d = 0;
    if (IsKeyDown(KEY_W)) {
        speed += acceleration * deltaTime;
        w = 10;
        s = -10;
    }
    if (IsKeyDown(KEY_S)) {
        speed -= acceleration * deltaTime;
        s = 10;
    }
    if (IsKeyDown(KEY_A)) {
        angle += 3 * deltaTime;
        direction -= (3 * (180/M_PI)) * deltaTime;
        a = 10;
    }
    if (IsKeyDown(KEY_D)) {
        angle -= 3 * deltaTime;
        direction += (3 * (180/M_PI)) * deltaTime;
        d = 10;
    }

    // // target.push_back(d);
    // // target.push_back(a);
    // // target.push_back(w);
    // // target.push_back(s);
    // for (int i=0; i < target.size(); i++) {
    //     std::cout << target.at(i) << " ";
    // }
    // std::cout << std::endl;
    // target = {0, 0, 1, 0};
    // std::vector<double> nactions = neuralNetwork.feedForward(offsets);
    // neuralNetwork.backPropogation(target, offsets);
    
        // std::cout << speed << " " << acceleration  << std::endl;
        // std::cout << deltaTime << std::endl << std::endl;
        // speed = 100;
    
    // if (IsKeyDown(KEY_ENTER)) {
        // std::cout << actions.at(0) << " " << actions.at(1) << " " << actions.at(2) << " " << actions.at(3) << std::endl;
        if ((actions.at(2) >= 0.5) && (actions.at(2) > actions.at(3))){
            speed += acceleration * deltaTime;
            w = 1;
        } 

        if ((actions.at(3) >= 0.5) && (actions.at(3) > actions.at(2))){
            speed -= acceleration * deltaTime;
            s = 1;
        }

        if ((actions.at(0) >= 0.5) && (actions.at(0) > actions.at(1))) {
            angle -= 3 * deltaTime;
            direction += (3 * (180/M_PI)) * deltaTime;
            d = 0;
        }
        if ((actions.at(1) >= 0.5) && (actions.at(1) > actions.at(0))) {
            angle += 3 * deltaTime;
            direction -= (3 * (180/M_PI)) * deltaTime;
            a = 0;
        }
        
    // }

    target.push_back(d);
    target.push_back(a);
    target.push_back(w);
    target.push_back(s);
    
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
    // speed = maxSpeed;
    std::vector<Vector3> offsetVec = rays.hitCoordVec3;
    std::vector<double> offsets2;
    for (int i=0; i < offsetVec.size(); i++) {
        if (offsetVec.at(i).z == 0) {
            offsets2.push_back(0);
        } else {
            offsets2.push_back(1 - offsetVec.at(i).z);
        }
    }
    std::vector<double> nactions = neuralNetworkUpdate.feedForward(offsets);
    std::vector<double> nactions2 = neuralNetworkUpdate2.feedForward(offsets);

    std::vector<double>* targetPtr = new std::vector<double>(target);
    std::vector<double>* offsetsPtr = new std::vector<double>(offsets);

    std::vector<double> newvector = {1-target.at(0), 1-target.at(1), 1-target.at(2), 1-target.at(3)};
    std::vector<double>* newvectorPtr = new std::vector<double>(newvector);
    
    neuralNetworkUpdate.backPropogation(targetPtr, offsetsPtr);
    neuralNetworkUpdate2.backPropogation(newvectorPtr, offsetsPtr);

    delete targetPtr;
    delete offsetsPtr;
    delete newvectorPtr;
    // if (checkPointCollision(map)) {
    //     std::cout << "ja" << std::endl;
    //     timeSinceLastPoint = 0;
    //     neuralNetwork = neuralNetworkUpdate;
    // }
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
        // x = NULL;
        // y = NULL;
        // std::cout << "ja " << "kaas" <<  "nee" << std::endl;
        delete x;
        delete y;
        x = NULL;
        y = NULL;
        // std::cout << "ja " << "nee" << std::endl;
        // double epsilon = 1;
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
        // std::cout << outputs[0] << " " << outputs[1] << " " << outputs[2] << " " << outputs[3] << std::endl;
        
        // outputsbool.clear();
        // for (int i=0; i < 4; i++) {
        //     outputsbool.push_back(outputs[i]);
        // }
        if (checkPointCollision(map)) {
            timeSinceLastPoint = 0;
            neuralNetwork = neuralNetworkUpdate;
            neuralNetworkUpdate2 = neuralNetworkUpdate;
            // std::cout << "ja" << std::endl;
            currentPoints++;
            // std::vector<double> target = neuralNetwork.feedForward(offsets);
            // std::vector<double> nactions = neuralNetwork.feedForward(offsets);
            // neuralNetwork.backPropogation({1,0,1,0}, offsets);
        }
        // if (test) {
        // }
        timeSinceLastPoint += deltaTime;
        if (timeSinceLastPoint >= 20) {
            alive = false;
            // std::cout << timeSinceLastPoint << std::endl;
            timeSinceLastPoint = 0;
            // std::cout << "ja"<< std::endl;
        } 
        // std::cout << timeSinceLastPoint << std::endl;
        // if (timeSinceLastPoint > 1) {
        //     std::cout << timeSinceLastPoint << std::endl;
        // }
        // std::cout << timeSinceLastPoint;
        // if (collectedPoints != 0) {
        // std::cout << collectedPoints << std::endl;
        std::vector<double>* offsettsp = new std::vector<double>(offsets);
        // int action = Qtable.makeDecision(offsettsp);
        
        
        // offsets.push_back(speed);
        // offsets.push_back(speed);
        std::vector<double> actions = neuralNetwork.feedForward(offsets);
        // neuralNetwork.backPropogation({-1, 0.3, 1, -1}, offsets);
        
        for (int i=0; i < actions.size(); i++) {
            std::cout << actions.at(i) << " ";
        }
        std::cout << "\n";
        move2(deltaTime, actions, offsets, map, epsilon);
        previousState4 = previousState3;
        previousState3 = previousState2;
        previousState2 = previousState1;
        previousState1 = previousState;
        previousState = offsets;
        previousStates.clear();
        previousStates.push_back(previousState);
        previousStates.push_back(previousState1);
        previousStates.push_back(previousState2);
        previousStates.push_back(previousState3);
        previousStates.push_back(previousState4);
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
        

    } 
    else {
        neuralNetwork = neuralNetworkUpdate2;
    }
    // map = NULL;
    // delete map;
}

std::vector<std::vector<double>>* Car::returnPreviousStates() {
    std::vector<std::vector<double>>* previousStatesP = new std::vector<std::vector<double>>(previousStates);
    return previousStatesP;
}
