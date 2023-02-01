#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>

double lerp(double A, double B, double t) {
    double value = A + (B-A) *t;
    return value;
}

class GNNLevel {
    public:
        GNNLevel(int inputCount, int outpuCount);
        std::vector<double> FeedForward(std::vector<double> *neuralNetworkInputValues);
        double sigmoid(double x);
        double relu(double x);
        std::vector<std::vector<double>> weights;
        std::vector<double> biases;
        std::vector<double> levelNeuronOutputValue, networkNetValues;
        int levelInputCount, levelOutputCount;
    private:
};

// fills the wieghts and biases of a level with random numbers
GNNLevel::GNNLevel(int inputCount, int outpuCount) {
    levelInputCount = inputCount;
    levelOutputCount = outpuCount;
    for (int i=0; i < outpuCount; i++) {
        std::vector<double> neuronWeights;
        for (int j=0; j < inputCount; j++) {
            double randval = rand() % 100;
            double randomdouble = randval/100;
            int negativeOrPositive = rand() % 2;
            if (negativeOrPositive == 0){
                neuronWeights.push_back(randomdouble);
            } else {
                randomdouble = -randomdouble;
                neuronWeights.push_back(randomdouble);
            }
        }
        weights.push_back(neuronWeights);
        double randval = rand() % 100;
        double randomdouble = randval/100;
        biases.push_back(randomdouble);
    }
}

// calculates the output of this layer/level and returns it to be used as input for the next layer/level
std::vector<double> GNNLevel::FeedForward(std::vector<double> *neuralNetworkInputValues) {
    levelNeuronOutputValue.clear();
    networkNetValues.clear();
    for (int i=0; i < levelOutputCount; i++) {
        double neuronValue, neuronValueSigmoid;
        for (int j=0; j < levelInputCount; j++) {
            neuronValue += weights.at(i).at(j) * neuralNetworkInputValues->at(j);
        }
        networkNetValues.push_back(neuronValue - biases.at(i));
        neuronValueSigmoid = relu(neuronValue - biases.at(i));
        levelNeuronOutputValue.push_back(neuronValueSigmoid);
    }
    return levelNeuronOutputValue;
}

double GNNLevel::sigmoid(double x) { // sigmoid function returns a value between 0 and 1
    double e = exp(-x);
    double value = 1 / (1 + e);
    return value;
}

double GNNLevel::relu(double x) { // relu function  
    if (x > 0) {
        return x;
    } else {
        return 0;
    }
}

class GeneticNeuralNetwork {
    public:
        GeneticNeuralNetwork(std::vector<int> neuralNetworkLevels = {8, 6, 4});
        std::vector<double> feedForward(std::vector<double> networkInputValues);
        void saveNeuralNetwork();
        void loadNeuralNetwork(nlohmann::json networkData);
        void mutate(double mutationRate);
        std::vector<GNNLevel> levels;
        std::vector<double> networkOutput;
        std::vector<double> networkError;
        std::vector<std::vector<std::vector<double>>> newWeigths, newWeightsUpdate;
        std::vector<std::vector<double>> newBiases, newBiasesUpdate;
        double errorSum, timesRun;
        std::vector<double> networkInput;
    private:
};

// calls the GNNLevel constructor to create an neuralnetwork with acorcingly to the given blueprint (neuralNetworkLevels)
GeneticNeuralNetwork::GeneticNeuralNetwork(std::vector<int> neuralNetworkLevels) {
    for (int i=0; i < neuralNetworkLevels.size()-1; i++) {
        GNNLevel level(neuralNetworkLevels.at(i), neuralNetworkLevels.at(i+1));
        levels.push_back(level);
    }
    timesRun = 0;
}

std::vector<double> GeneticNeuralNetwork::feedForward(std::vector<double> networkInputValues) {
    networkInput = networkInputValues;
    std::vector<double> neuralNetworkInputValues = networkInputValues;
    for (int i=0; i < levels.size(); i++) {
        neuralNetworkInputValues = levels.at(i).FeedForward(&neuralNetworkInputValues);
    }
    networkOutput = neuralNetworkInputValues;
    return networkOutput;
}

// mutates the neuralnetwork using lerp, random numbers and a mutationRate the lower the mutationRate the less it mutates
void GeneticNeuralNetwork::mutate(double mutationRate) {
    for (int i=0; i < levels.size(); i++) {
        for (int j=0; j < levels.at(i).biases.size(); j++) {
            double v1 = rand() % 1000000000;
            levels.at(i).biases.at(j) = lerp(levels.at(i).biases.at(j), (v1/1000000000)*2-1, mutationRate);
        }

        for (int j=0; j < levels.at(i).weights.size(); j++) {
            for (int k=0; k < levels.at(i).weights.at(j).size(); k++) {
                double v1 = rand() % 1000000000;
                levels.at(i).weights.at(j).at(k) = lerp(levels.at(i).weights.at(j).at(k), (v1/1000000000)*2-1, mutationRate);
            }
        }
    }
}

// saves the neuralnetwork to an json file
void GeneticNeuralNetwork::saveNeuralNetwork() {
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
    testfile.open ("NeuralNetworks/GNN.json");
    testfile << jsonfile;
    testfile.close();
}

// loads a neurlnetwork from an json file using an nlohmann::json type as input
void GeneticNeuralNetwork::loadNeuralNetwork(nlohmann::json networkData) {    
    int lenght1 = networkData["weights"]["lenght"].get<int>();
    int lenght2 = networkData["biases"]["lenght"].get<int>();

    for (int i=0; i < lenght1; i++) {
        int lenghti = networkData["weights"][std::to_string(i)]["lenght"].get<int>();
        for (int j=0; j < lenghti; j++) {
            int lenghtj = networkData["weights"][std::to_string(i)][std::to_string(j)]["lenght"].get<int>();
            for (int k=0; k < lenghtj; k++) {
                levels.at(i).weights.at(j).at(k) = networkData["weights"][std::to_string(i)][std::to_string(j)][std::to_string(k)].get<double>();
            }
        }
        int lenghti2 = networkData["biases"][std::to_string(i)]["lenght"].get<int>();
        for (int j=0; j < lenghti2; j++) {
            levels.at(i).biases.at(j) = networkData["biases"][std::to_string(i)][std::to_string(j)].get<double>();
        }
    }
}