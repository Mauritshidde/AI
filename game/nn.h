#include <vector>
#include <cstdlib>
#include <string>
#include <nlohmann/json.hpp>

#include "aiLevel.h"

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

class GeneticNeuralNetwork {
    public:
        GeneticNeuralNetwork(std::vector<int> neuronCounts = {8, 6, 6, 6, 4});
        std::vector<double> feedforward(std::vector<double> givenInputs, GeneticNeuralNetwork network);
        void mutate(GeneticNeuralNetwork network, double amount);
        void saveNN();
        void setNN(GeneticNeuralNetwork network);
        std::vector<Level> levels;
    private:
};

GeneticNeuralNetwork::GeneticNeuralNetwork(std::vector<int> neuronCounts) {
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

std::vector<double> GeneticNeuralNetwork::feedforward(std::vector<double> givenInputs, GeneticNeuralNetwork network) {
    std::vector<double> outputs;
    outputs = levels.at(0).feedForward(givenInputs, levels.at(0));
    for (int i=1; i < levels.size(); i++) {
        outputs = levels.at(0).feedForward(outputs, levels.at(i));
    }
    return outputs;
}

void GeneticNeuralNetwork::mutate(GeneticNeuralNetwork network, double amount) {
    for (int i=0; i < network.levels.size(); i++) {
        for (int j=0; j < network.levels.at(i).biases.size(); j++) {
            double v1 = rand() % 1000000000;
            levels.at(i).biases.at(j) = lerp(network.levels.at(i).biases.at(j), (v1/1000000000)*2-1, amount);
        }

        for (int j=0; j < network.levels.at(i).weights.size(); j++) {
            for (int k=0; k < network.levels.at(i).weights.at(j).size(); k++) {
                double v1 = rand() % 1000000000;
                levels.at(i).weights.at(j).at(k) = lerp(network.levels.at(i).weights.at(j).at(k), (v1/1000000000)*2-1, amount);
            }
        }
    }
}

void GeneticNeuralNetwork::setNN(GeneticNeuralNetwork network) {
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

void GeneticNeuralNetwork::saveNN() {
    nlohmann::json jsonfile;

    jsonfile["weights"]["lenght"] = levels.size();
    jsonfile["biases"]["lenght"] = levels.size();

    for (int i=0; i < levels.size(); i++) {
        jsonfile["weights"][std::to_string(i)]["lenght"] = levels.at(i).weights.size();
        for (int j=0; j < levels.at(i).weights.size(); j++) {
            jsonfile["weights"][std::to_string(i)][std::to_string(j)]["lenght"] = levels.at(i).weights.at(j).size();
            for (int k=0; k < levels.at(i).weights.at(j).size(); k++) {
                jsonfile["weights"][std::to_string(i)][std::to_string(j)][std::to_string(k)] = levels.at(i).weights.at(j).at(k);
            }
        }
        jsonfile["biases"][std::to_string(i)]["lenght"] = levels.at(i).biases.size();
        for (int j=0; j < levels.at(i).biases.size(); j++) {
            jsonfile["biases"][std::to_string(i)][std::to_string(j)] = levels.at(i).biases.at(j);
        }
    }

    std::ofstream testfile;
    testfile.open ("NeuralNetworks/NN.json");
    testfile << jsonfile;
    testfile.close();
}