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

double derivativeSigmoid(double Zj) {
    double sigmoidDerivative, sigmoid1, sigmoid2;
    sigmoid1 = 1 /(1+exp(-Zj));
    sigmoid2 = 1 - (1/(1+exp(-Zj)));
    sigmoidDerivative = sigmoid1 * sigmoid2;
    return sigmoidDerivative;
}

void propagate(std::vector<double> inputs, std::vector<double> outputValues, std::vector<double> targets, NNLevel level) {
    std::vector<std::vector<double>> newWeightValues;
    double Zj;

    // for (int i=0; i < outputValues.size(); i++) {
    //     for (int j=0; j < inputs.size(); j++) {
    //         Zj += level.weights.at(j).at(i) * level.levelNeuronOutputValue.at(j);
    //     }
    // }
    
    // double dATOdZ = derivativeSigmoid(Zj); // derivative A0 / derivative Zj

    // for (int i=0; outputValues.size(); i++) {
    //     std::vector<double> newWeights;
    //     for (int j=0; j < inputs.size(); j++) {
    //         level.weights.at(j).at(i); // for the first output neuron the first weight of all input neurons is used
    //         double a = inputs.at(j);
    //         double costWeight = 2 * (targets.at(j));
    //         double costOverWeightRatio;
    //         // newWeights.push_back();
    //     }
    //     newWeightValues.push_back(newWeights);
    // }

    std::vector<std::vector<double>> weightGradients;
    for (int i=0; i < outputValues.size(); i++) {
        double dATOdZ = derivativeSigmoid(Zj); // derivative A / derivative Z

        std::vector<double> weightGradient;
        for (int j=0; j < level.weights.at(i).size(); j++) {
            double a = inputs.at(j);
            double Aj = 2 * (level.levelNeuronOutputValue.at(i) - targets.at(i));

            double costOverWeightRatio = a * Aj * dATOdZ;
            weightGradient.push_back(costOverWeightRatio);
        }
        weightGradients.push_back(weightGradient);
    }

    std::vector<double> biasGradients;
    for (int i=0; i < outputValues.size(); i++) {
        double dATOdZ = derivativeSigmoid(Zj); // derivative A / derivative Z
        double Aj = 2 * (level.levelNeuronOutputValue.at(i) - targets.at(i));

        double costOverWeightRatio = 1 * Aj * dATOdZ;
        biasGradients.push_back(costOverWeightRatio);
    }

    // calculate the partial derivitive of the total cost to the derivative of the input layers neuron
    for (int i=0; i < inputs.size(); i++) { 
        for (int j=0; j < outputValues.size(); j++) {
            for (int k=0; k < level.weights.at(i).size(); k++) {

            }
        }
        double derivitiveSum;
        for (int j=0; j < outputValues.size(); j++) {
            derivitiveSum +=  2;
        }
    }

    std::vector<double> nextLayerTarget;
    for (int k=0; k < inputs.size(); k++) {
        double nextNeuronValue;

        for (int i=0; i < outputValues.size(); i++) {
            double dATOdZ = derivativeSigmoid(Zj); // derivative A / derivative Z
            
            double weight = level.weights.at(i).at(k);
            double Aj = 2 * (level.levelNeuronOutputValue.at(i) - targets.at(i));
    
            double costOverWeightRatio = weight * Aj * dATOdZ;
            nextNeuronValue += costOverWeightRatio;
            // std::vector<double> weightGradient;
            // for (int j=0; j < level.weights.at(i).size(); j++) {
            //     double weight = level.weights.at(j).at(k);
            //     double Aj = 2 * (level.levelNeuronOutputValue.at(j) - targets.at(j));
        
            //     double costOverWeightRatio = weight * Aj * dATOdZ;
            //     nextNeuronValue += costOverWeightRatio;
            // }
            // weightGradients.push_back(weightGradient);

        }
        nextLayerTarget.push_back(nextNeuronValue);
    }

    // change weights and biases by learning rate
    double learningRate = 0.5;
    for (int i=0; i < outputValues.size(); i++) {
        for (int j=0; j < level.weights.at(i).size(); j++) {
            double newWeight = level.weights.at(i).at(j) + learningRate * weightGradients.at(i).at(j);
            level.weights.at(i).at(j) = newWeight;
        }

        double newBias = level.biases.at(i) + learningRate * biasGradients.at(i);
        level.biases.at(i) = newBias;
    }

    // for (int i=0; i < outputValues.size(); i++) {
    //     for (int j=0; j < level.weights.at(i).size(); j++) {
        
    //     }
    // }

    // nextLayerTarget this vector is used to 
    // weightGradients
    // biasGradients
}

void NeuralNetwork::backPropogation() {
    for (int i=levels.size()-1; 0 <= i; i--) { // loop backwards trough te levels for backpropagation
        if (i == 0) {

        } else {
            levels.at(i);

        }
    }
}

int main() {
    // NNLevel level();



    return 0;
}