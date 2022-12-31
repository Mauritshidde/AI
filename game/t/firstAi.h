#include <vector>
#include <cstdlib>

#include "aiLevel.h"

class NeuralNetwork {
    public:
        NeuralNetwork(std::vector<int> neuronCounts);
        std::vector<double> feedforward(std::vector<double> givenInputs, NeuralNetwork network);
    private:
        std::vector<Level> levels;
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
        outputs = levels.at(0).feedForward(outputs, levels.at(i));
    }
    return outputs;
}

