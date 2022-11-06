#include <iostream>
#include <vector>
#include <cmath>


class NNLevel {
    public:
        NNLevel(int inputCount, int outpuCount);
        std::vector<double> feedForward(std::vector<double> neuralNetworkInputValues);
        double sigmoid(double x);
        std::vector<std::vector<double>> weights;
        std::vector<double> biases;
        std::vector<double> levelNeuronOutputValue, networkNetValues;
        int levelInputCount, levelOutputCount;
    private:
};

NNLevel::NNLevel(int inputCount, int outpuCount) {
    levelInputCount = inputCount;
    levelOutputCount = outpuCount;
    for (int i=0; i < outpuCount; i++) {
        std::vector<double> neuronWeights;
        for (int j=0; j < inputCount; j++) {
            neuronWeights.push_back(0.5);
        }
        weights.push_back(neuronWeights);
        biases.push_back(0.7);
    }
}

std::vector<double> NNLevel::feedForward(std::vector<double> neuralNetworkInputValues) {
    levelNeuronOutputValue.clear();
    networkNetValues.clear();
    for (int i=0; i < levelOutputCount; i++) {
        double neuronValue, neuronValueSigmoid;
        for (int j=0; j < levelInputCount; j++) {
            neuronValue += weights.at(i).at(j) * neuralNetworkInputValues.at(j);
        }
        networkNetValues.push_back(neuronValue - biases.at(i));
        neuronValueSigmoid = sigmoid(neuronValue - biases.at(i));
        levelNeuronOutputValue.push_back(neuronValueSigmoid);
    }
    return levelNeuronOutputValue;
}

double NNLevel::sigmoid(double x) {
    double e = exp(-x);
    double value = 1 / (1 + e);
    return value;
}

class NeuralNetwork {
    public:
        NeuralNetwork(std::vector<int> neuralNetworkLevels);
        void feedForward(std::vector<double> networkInputValues);
        void GradientError(std::vector<double> target);
        void backPropogation();
        std::vector<NNLevel> levels;
        std::vector<double> networkOutput;
        std::vector<double> networkError;
        double errorSum;
    private:
};

NeuralNetwork::NeuralNetwork(std::vector<int> neuralNetworkLevels) {
    for (int i=0; i < neuralNetworkLevels.size()-1; i++) {
        NNLevel level(neuralNetworkLevels.at(i), neuralNetworkLevels.at(i+1));
        levels.push_back(level);
    }
}

void NeuralNetwork::feedForward(std::vector<double> networkInputValues) {
    std::vector<double> neuralNetworkInputValues = networkInputValues;
    for (int i=0; i < levels.size(); i++) {
        neuralNetworkInputValues = levels.at(i).feedForward(neuralNetworkInputValues);
    }
    networkOutput = neuralNetworkInputValues;
}

void NeuralNetwork::GradientError(std::vector<double> target) {
    errorSum = 0;
    for (int i=0; i < networkOutput.size(); i++) {
        double error = 0.5 * (target.at(i) - networkOutput.at(i));
        networkError.push_back(error);
        errorSum += error;
    }
}

void NeuralNetwork::backPropogation() {
    for (int i=levels.size(); 0 < i; i--) { // loop backwards trough te levels for backpropagation
        double dt = 1/INFINITY;
        for (int i=0; i < levels.at(i-1).levelNeuronOutputValue.size(); i++) {
            
        }
        
    }
}

int main() {
    // NNLevel level();



    return 0;
}