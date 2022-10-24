#include <vector>
#include <cstdlib>
#include <string>
#include <nlohmann/json.hpp>

#include "aiLevel.h"

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

class NeuralNetwork {
    public:
        NeuralNetwork(std::vector<int> neuronCounts);
        std::vector<double> feedforward(std::vector<double> givenInputs, NeuralNetwork network);
        void saveNN();
        void setNN(NeuralNetwork network);
        std::vector<Level> levels;
    private:
};

NeuralNetwork::NeuralNetwork(std::vector<int> neuronCounts) {
    for (int i=0; i < neuronCounts.size(); i++) {
        if (i == neuronCounts.size()-1) {

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

void NeuralNetwork::setNN(NeuralNetwork network) {
    for (int i=0; i < network.levels.size(); i++) {
        for (int j=0; j < network.levels.at(i).biases.size(); j++) {
            double v1 = rand() % 100;
            levels.at(i).biases.at(j) = network.levels.at(i).biases.at(j);
        }

        for (int j=0; j < network.levels.at(i).weights.size(); j++) {
            for (int k=0; k < network.levels.at(i).weights.at(j).size(); k++) {
                // double v1 = rand() % 100;
                levels.at(i).weights.at(j).at(k) = network.levels.at(i).weights.at(j).at(k);
            }
        }
    }
}

void NeuralNetwork::saveNN() {
    nlohmann::json jsonfile;

    jsonfile["weights"]["lenght"] = levels.size();
    jsonfile["biases"]["lenght"] = levels.size();

    for (int i=0; i < levels.size(); i++) {
        jsonfile["weights"][std::to_string(i)]["lenght"] = levels.at(i).weights.size();
        for (int j=0; j < levels.at(i).weights.size(); j++) {
            jsonfile["weights"][std::to_string(i)][std::to_string(j)]["lenght"] = levels.at(i).weights.at(j).size();
            for (int k=0; k < levels.at(i).weights.at(j).size(); k++) {
                jsonfile["weights"][std::to_string(i)][std::to_string(j)][std::to_string(k)] = levels.at(i).weights.at(j).at(k);
                // j["weights"][std::to_string(j)][k][levels.at(i).weights.at(j).at(k)];
            }
        }
        jsonfile["biases"][std::to_string(i)]["lenght"] = levels.at(i).biases.size();
        for (int j=0; j < levels.at(i).biases.size(); j++) {
            jsonfile["biases"][std::to_string(i)][std::to_string(j)] = levels.at(i).biases.at(j);
        }
    }

    std::ofstream testfile;
    testfile.open ("NN.json");
    testfile << jsonfile;
    testfile.close();
}