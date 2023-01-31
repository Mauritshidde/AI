#include <vector>
#include <raylib.h>
#include "QCar.h"

class VisualiseNN {
    public:
        VisualiseNN(Car* newCar);
        void DrawNeuralNetwork();
        std::vector<std::vector<Vector2>> neuronLocation;
        Car* car;
};

VisualiseNN::VisualiseNN(Car* newCar) {
    car = newCar;
    std::vector<Vector2> firstLayerLocation;
    for (int i=0; i < car->neuralNetwork.levels.at(0).levelInputCount; i++) {
        Vector2 location = {180 ,float(200+i*30)};
        firstLayerLocation.push_back(location);
    }
    neuronLocation.push_back(firstLayerLocation);
    for (int j=0; j < car->neuralNetwork.levels.size(); j++) {
        std::vector<Vector2> layerNeuronLocation;
        for (int i=0; i < car->neuralNetwork.levels.at(j).weights.size(); i++) {
            Vector2 location = {float(290+j*110), float(200+i*30)};
            layerNeuronLocation.push_back(location);
        }
        neuronLocation.push_back(layerNeuronLocation);
    }
}

void VisualiseNN::DrawNeuralNetwork() {
    for (int i=0; i < neuronLocation.size(); i++) {
        for (int j=0; j < neuronLocation.at(i).size(); j++) {
            if (i == 0) {
                if (car->neuralNetwork.networkInput.at(j) >= 0.5) {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, RED); 
                } else {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, WHITE); 
                }
            } else {
                if (car->neuralNetwork.levels.at(i-1).levelNeuronOutputValue.at(j) >= 0.5) {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, RED); 
                } else {
                    DrawCircle(neuronLocation.at(i).at(j).x, neuronLocation.at(i).at(j).y, 7, WHITE); 
                }
            }
        }
    }
    
    for (int i=0; i < car->neuralNetwork.levels.size(); i++) {
        for (int j=0; j < car->neuralNetwork.levels.at(i).weights.size(); j++) {
            for (int k=0; k < car->neuralNetwork.levels.at(i).weights.at(j).size(); k++) {
                if (car->neuralNetwork.levels.at(i).weights.at(j).at(k) >= 0){
                    DrawLineV(neuronLocation.at(i+1).at(j), neuronLocation.at(i).at(k), RED);
                } else {
                    DrawLineV(neuronLocation.at(i+1).at(j), neuronLocation.at(i).at(k), WHITE);
                }
            }  
        }
    }
}