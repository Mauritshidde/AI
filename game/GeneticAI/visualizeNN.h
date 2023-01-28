#include <vector>
#include <raylib.h>

class VisualiseGNN {
    public:
        VisualiseGNN(GCar* newCar, Vector2 newBox[4]);
        void setBox(Vector2 newBox[4]);
        void DrawNeuralNetwork();
        std::vector<std::vector<Vector2>> neuronLocation;
        GCar* car;
        Vector2 box[4];
        float smallestX, smallestY;
        float highestX, highestY;
};

VisualiseGNN::VisualiseGNN(GCar* newCar, Vector2 newBox[4]) {
    car = newCar;
    box[0] = newBox[0];
    box[1] = newBox[1];
    box[2] = newBox[2];
    box[3] = newBox[3];

    int smallestXIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].x <= box[smallestXIndex].x) {
            smallestXIndex = i;
            smallestX = box[i].x;
        }
    }

    int smallestYIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].y <= box[smallestYIndex].y) {
            smallestYIndex = i;
            smallestY = box[i].y;
        }
    }

    int highestXIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].x >= box[highestXIndex].x) {
            highestXIndex = i;
            highestX = box[i].x;
        }
    }

    int highestYIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].y >= box[highestYIndex].y) {
            highestYIndex = i;
            highestY = box[i].y;
        }
    }
    std::vector<Vector2> firstLayerLocation;
    for (int i=0; i < car->network.levels.at(0).levelInputCount; i++) {
        float v = (highestY-smallestY)/(car->network.levels.at(0).levelInputCount-1);
        Vector2 location = {smallestX ,float(smallestY+i*v)};
        firstLayerLocation.push_back(location);
    }
    neuronLocation.push_back(firstLayerLocation);
    for (int j=0; j < car->network.levels.size(); j++) {
        float v2 = (highestX-smallestX)/(car->network.levels.size());
        std::vector<Vector2> layerNeuronLocation;
        for (int i=0; i < car->network.levels.at(j).weights.size(); i++) {
            float v = (highestY-smallestY)/(car->network.levels.at(j).weights.size()-1);
            Vector2 location = {float(smallestX+(j+1)*v2), float(smallestY+i*v)};
            layerNeuronLocation.push_back(location);
        }
        neuronLocation.push_back(layerNeuronLocation);
    }
}

void VisualiseGNN::setBox(Vector2 newBox[4]) {
    neuronLocation.clear();
    box[0] = newBox[0];
    box[1] = newBox[1];
    box[2] = newBox[2];
    box[3] = newBox[3];

    int smallestXIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].x < box[smallestXIndex].x) {
            smallestXIndex = i;
            smallestX = box[i].x;
        }
    }

    int smallestYIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].y < box[smallestYIndex].y) {
            smallestYIndex = i;
            smallestY = box[i].y;
        }
    }

    int highestXIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].x > box[highestXIndex].x) {
            highestXIndex = i;
            highestX = box[i].x;
        }
    }

    int highestYIndex = 0; 
    for (int i=0; i < 4; i++) {
        if (box[i].y > box[highestYIndex].y) {
            highestYIndex = i;
            highestY = box[i].y;
        }
    }

    std::vector<Vector2> firstLayerLocation;
    for (int i=0; i < car->network.levels.at(0).levelInputCount; i++) {
        float v = (highestY-smallestY)/(car->network.levels.at(0).levelInputCount-1);
        Vector2 location = {smallestX ,float(smallestY+i*v)};
        firstLayerLocation.push_back(location);
    }
    neuronLocation.push_back(firstLayerLocation);
    for (int j=0; j < car->network.levels.size(); j++) {
        float v2 = (highestX-smallestX)/(car->network.levels.size());
        std::vector<Vector2> layerNeuronLocation;
        for (int i=0; i < car->network.levels.at(j).weights.size(); i++) {
            float v = (highestY-smallestY)/(car->network.levels.at(j).weights.size()-1);
            Vector2 location = {float(smallestX+(j+1)*v2), float(smallestY+i*v)};
            layerNeuronLocation.push_back(location);
        }
        neuronLocation.push_back(layerNeuronLocation);
    }
}

void VisualiseGNN::DrawNeuralNetwork() {
    for (int i=0; i < neuronLocation.size(); i++) {
        for (int j=0; j < neuronLocation.at(i).size(); j++) {
            if (i == 0) {
                if (car->network.networkInput.at(j) >= 0.5) {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, RED); 
                } else {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, WHITE); 
                }
            } else {
                if (car->network.levels.at(i-1).levelNeuronOutputValue.at(j) >= 0.5) {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, RED); 
                } else {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, WHITE); 
                }
            }
        }
    }
    
    for (int i=0; i < car->network.levels.size(); i++) {
        for (int j=0; j < car->network.levels.at(i).weights.size(); j++) {
            for (int k=0; k < car->network.levels.at(i).weights.at(j).size(); k++) {
                if (car->network.levels.at(i).weights.at(j).at(k) >= 0){
                    DrawLineV(neuronLocation.at(i+1).at(j), neuronLocation.at(i).at(k), RED);
                } else {
                    DrawLineV(neuronLocation.at(i+1).at(j), neuronLocation.at(i).at(k), WHITE);
                }
            }  
        }
    }
}