#include <vector>
#include <cstdlib>

#include "aiLevel.h"

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

class NeuralNetwork {
    public:
        NeuralNetwork(std::vector<int> neuronCounts = {4, 16, 8});
        std::vector<double> feedforward(std::vector<double> givenInputs, NeuralNetwork network);
        void mutate(NeuralNetwork network, double amount);
        void saveNN();
        void setNN(NeuralNetwork network);
        std::vector<Level> levels;
    private:
};

NeuralNetwork::NeuralNetwork(std::vector<int> neuronCounts) {
    for (int i=0; i < neuronCounts.size(); i++) {
        if (i == neuronCounts.size()-1) {
            Level leveltje(neuronCounts.at(i),neuronCounts.at(0));
            levels.push_back(leveltje);
        } else {
            Level leveltje(neuronCounts.at(i),neuronCounts.at(i+1));      
            levels.push_back(leveltje);
        }
    }
}

std::vector<double> NeuralNetwork::feedforward(std::vector<double> givenInputs, NeuralNetwork network) {
    std::vector<double> outputs;
    // std::cout << givenInputs.at(1) << " we1" << std::endl;
    outputs = levels.at(0).feedForward(givenInputs, levels.at(0));
    for (int i=1; i < levels.size(); i++) {
        outputs = levels.at(i).feedForward(outputs, levels.at(i));
    }
    return outputs;
}

void NeuralNetwork::mutate(NeuralNetwork network, double amount) {
    amount = 0.1;
    
    for (int i=0; i < network.levels.size(); i++) {
        // std::cout << network.levels.at(i).biases.size() << "  ";
        for (int j=0; j < network.levels.at(i).biases.size(); j++) {
            double v1 = rand() % 100;
            levels.at(i).biases.at(j) = lerp(network.levels.at(i).biases.at(j), (v1/100)*2-1, amount);
            // double test = lerp(network.levels.at(i).biases.at(j), (v1/100)*2-1, amount);
            // std::cout << test << " ";
        }

        for (int j=0; j < network.levels.at(i).weights.size(); j++) {
            for (int k=0; k < network.levels.at(i).weights.at(j).size(); k++) {
                double v1 = rand() % 100;
                levels.at(i).weights.at(j).at(k) = lerp(network.levels.at(i).weights.at(j).at(k), (v1/100)*2-1, amount);
            }
        }
    }
}

void NeuralNetwork::setNN(NeuralNetwork network) {
    for (int i=0; i < network.levels.size(); i++) {
        for (int j=0; j < network.levels.at(i).biases.size(); j++) {
            double v1 = rand() % 100;
            levels.at(i).biases.at(j) = network.levels.at(i).biases.at(j);
        }

        for (int j=0; j < network.levels.at(i).weights.size(); j++) {
            for (int k=0; k < network.levels.at(i).weights.at(j).size(); k++) {
                double v1 = rand() % 100;
                levels.at(i).weights.at(j).at(k) = network.levels.at(i).weights.at(j).at(k);
            }
        }
    }
}

void NeuralNetwork::saveNN() {
    
}