#include <vector>
#include <raylib.h>

class VisualiseGNN {
    public:
        VisualiseGNN(GCar* newCar);
        void DrawNeuralNetwork();
        std::vector<std::vector<Vector2>> neuronLocation;
        GCar* car;
};

VisualiseGNN::VisualiseGNN(GCar* newCar) {
    car = newCar;
    std::vector<Vector2> firstLayerLocation;
    for (int i=0; i < car->network.levels.at(0).levelInputCount; i++) {
        Vector2 location = {180 ,float(200+i*30)};
        firstLayerLocation.push_back(location);
    }
    neuronLocation.push_back(firstLayerLocation);
    for (int j=0; j < car->network.levels.size(); j++) {
        std::vector<Vector2> layerNeuronLocation;
        for (int i=0; i < car->network.levels.at(j).weights.size(); i++) {
            Vector2 location = {float(290+j*110), float(200+i*30)};
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