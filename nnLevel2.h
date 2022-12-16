#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

class NNLevel {
    public:
        NNLevel(int inputCount, int outpuCount);
        std::vector<double> FeedForward(std::vector<double> neuralNetworkInputValues);
        double sigmoid(double x);
        std::vector<std::vector<double>> weights;
        std::vector<double> biases;
        std::vector<double> levelNeuronOutputValue, networkNetValues;
        int levelInputCount, levelOutputCount;
    private:
};

NNLevel::NNLevel(int inputCount, int outpuCount) {
    srand(time(NULL));
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
            // neuronWeights.push_back(randomdouble);
        }
        weights.push_back(neuronWeights);
        double randval = rand() % 100;
        double randomdouble = randval/100;
        biases.push_back(0.7);
    }
}

std::vector<double> NNLevel::FeedForward(std::vector<double> neuralNetworkInputValues) {
    // srand(time(NULL));
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
        std::vector<double> feedForward(std::vector<double> networkInputValues);
        void GradientError(std::vector<double> target);
        std::vector<double> propagate(std::vector<double>* inputs, std::vector<double>* outputValues, std::vector<double>* targets, NNLevel* level, double* learningRate);
        std::vector<double> propagate2(std::vector<double>* inputs, std::vector<double>* outputValues, std::vector<double>* targets, NNLevel* level, double* learningRate);
        void backPropogation(std::vector<double>* newTargets, std::vector<double>* input);
        void saveNeuralNetwork();
        void loadNeuralNetwork(nlohmann::json networkData);
        std::vector<NNLevel> levels;
        std::vector<double> networkOutput;
        std::vector<double> networkError;
        std::vector<std::vector<std::vector<double>>> newWeigths, newWeightsUpdate;
        std::vector<std::vector<double>> newBiases, newBiasesUpdate;
        double errorSum, timesRun;
        std::vector<double> networkInput;
    private:
};

NeuralNetwork::NeuralNetwork(std::vector<int> neuralNetworkLevels) {
    for (int i=0; i < neuralNetworkLevels.size()-1; i++) {
        NNLevel level(neuralNetworkLevels.at(i), neuralNetworkLevels.at(i+1));
        levels.push_back(level);
    }
    timesRun = 0;
}

std::vector<double> NeuralNetwork::feedForward(std::vector<double> networkInputValues) {
    networkInput = networkInputValues;
    std::vector<double> neuralNetworkInputValues = networkInputValues;
    for (int i=0; i < levels.size(); i++) {
        neuralNetworkInputValues = levels.at(i).FeedForward(neuralNetworkInputValues);
    }
    networkOutput = neuralNetworkInputValues;
    return networkOutput;
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

std::vector<double> NeuralNetwork::propagate(std::vector<double>* inputs, std::vector<double>* outputValues, std::vector<double>* targets, NNLevel* level, double* learningRate) {
    std::vector<std::vector<double>> newWeightValues;
    std::vector<double> Zj;
    for (int i=0; i < outputValues->size(); i++) {
        double ZjValue;
        for (int j=0; j < inputs->size(); j++) {
            ZjValue += inputs->at(j) * level->weights.at(i).at(j);
        }
        ZjValue += level->biases.at(i);
        Zj.push_back(ZjValue);
        // std::cout << ZjValue << " ZJ ";
    }
    // std::cout << std::endl << std::endl;
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
    for (int i=0; i < outputValues->size(); i++) {
        double dATOdZ = derivativeSigmoid(Zj.at(i)); // derivative A / derivative Z

        std::vector<double> weightGradient;
        for (int j=0; j < level->weights.at(i).size(); j++) {
            double a = inputs->at(j);
            // double Aj = 2 * (level->levelNeuronOutputValue.at(i) - targets.at(i));
            double Aj = 2 * (inputs->at(j) - targets->at(i));

            double costOverWeightRatio = a * Aj * dATOdZ;
            weightGradient.push_back(costOverWeightRatio);
            // std::cout << costOverWeightRatio << " " << Aj << " " << a << " " << dATOdZ << " ddd ";
        }
        // std::cout << std::endl << std::endl;
        weightGradients.push_back(weightGradient);
    }
    // newWeightsUpdate.push_back(weightGradients);
    newWeightsUpdate.insert(newWeightsUpdate.begin(), weightGradients);

    std::vector<double> biasGradients;
    for (int i=0; i < outputValues->size(); i++) {
        double dATOdZ = derivativeSigmoid(Zj.at(i)); // derivative A / derivative Z
        double Aj = 2 * (level->levelNeuronOutputValue.at(i) - targets->at(i));

        double costOverWeightRatio = 1 * Aj * dATOdZ;
        biasGradients.push_back(costOverWeightRatio);
    }
    newBiasesUpdate.insert(newBiasesUpdate.begin(), biasGradients);

    // // calculate the partial derivitive of the total cost to the derivative of the input layers neuron
    // for (int i=0; i < inputs.size(); i++) { 
    //     for (int j=0; j < outputValues.size(); j++) {
    //         for (int k=0; k < level.weights.at(i).size(); k++) {

    //         }
    //     }
    //     double derivitiveSum;
    //     for (int j=0; j < outputValues.size(); j++) {
    //         derivitiveSum +=  2;
    //     }
    // }

    // std::vector<double> nextLayerTarget;
    // for (int k=0; k < outputValues.size(); k++) {
    //     double nextNeuronValue;

    //     for (int i=0; i < inputs.size(); i++) {
    //         double zA = level->weights.at(k).at(i);
    //         double dATOdZ = derivativeSigmoid(Zj.at(i)); // derivative A / derivative Z
            
    //         double weight = level->weights.at(i).at(k);
    //         double Aj = 2 * (level->levelNeuronOutputValue.at(i) - targets.at(i));
    //         // dit klopt /werkt niet
    //         double costOverWeightRatio = weight * Aj * dATOdZ;
    //         nextNeuronValue += costOverWeightRatio;
    //         // std::vector<double> weightGradient;
    //         // for (int j=0; j < level.weights.at(i).size(); j++) {
    //         //     double weight = level.weights.at(j).at(k);
    //         //     double Aj = 2 * (level.levelNeuronOutputValue.at(j) - targets.at(j));
        
    //         //     double costOverWeightRatio = weight * Aj * dATOdZ;
    //         //     nextNeuronValue += costOverWeightRatio;
    //         // }
    //         // weightGradients.push_back(weightGradient);

    //     }
    //     nextLayerTarget.push_back(nextNeuronValue);
    // }

    std::vector<double> nextLayerTarget;
    for (int i=0; i < inputs->size(); i++) {
        double derivative;
        for (int j=0; j < outputValues->size(); j++) {
            double w = level->weights.at(j).at(i);
            double a  = derivativeSigmoid(Zj.at(j));
            double Co = 2 * (outputValues->at(j) - targets->at(j));
            double v = w * a * Co;
            derivative += v;
        }
        nextLayerTarget.push_back(derivative);
    }
    // std::cout << nextLayerTarget.size() << " Q " << inputs.size() << std::endl;

    // change weights and biases by learning rate
    for (int i=0; i < outputValues->size(); i++) {
        for (int j=0; j < level->weights.at(i).size(); j++) {
            // std::cout << level->weights.at(i).at(j) << " " << weightGradients.at(i).at(j) << " ";
            double newWeight = level->weights.at(i).at(j) + (*learningRate * weightGradients.at(i).at(j));
            // std::cout << newWeight << " " << level->weights.at(i).at(j) << std::endl;
            level->weights.at(i).at(j) = newWeight;
        }

        double newBias = level->biases.at(i) + (*learningRate * biasGradients.at(i));
        level->biases.at(i) = newBias;
    }
    
    // for (int i=0; i < outputValues.size(); i++) {
    //     for (int j=0; j < level.weights.at(i).size(); j++) {
        
    //     }
    // }

    // nextLayerTarget this vector is used to 
    // weightGradients
    // biasGradients
    // std::cout << std::endl;
    std::vector<double> costs;
    for (int i=0; i < outputValues->size(); i++) {
        double value = pow((outputValues->at(i)-targets->at(i)),2);
        costs.push_back(value);
    }

    return nextLayerTarget;
    // return costs;
}

std::vector<double> NeuralNetwork::propagate2(std::vector<double>* inputs, std::vector<double>* outputValues, std::vector<double>* targets, NNLevel* level, double* learningRate) {
    std::vector<std::vector<double>> newWeightValues;
    std::vector<double> Zj, costs;

    for (int i=0; i < outputValues->size(); i++) {
        double ZjValue;
        for (int j=0; j < inputs->size(); j++) {
            ZjValue += inputs->at(j) * level->weights.at(i).at(j);
        }
        ZjValue += level->biases.at(i);
        Zj.push_back(ZjValue);
    }
    
    std::vector<std::vector<double>> weightGradients;
    for (int i=0; i < outputValues->size(); i++) {
        // std::cout << targets.size() << " t " << outputValues.size() << std::endl;
        double Aj = targets->at(i);
        double dATOdZ = derivativeSigmoid(Zj.at(i)); // derivative A / derivative Z

        std::vector<double> weightGradient;
        for (int j=0; j < level->weights.at(i).size(); j++) {
            double a = inputs->at(j);
            // double Aj = 2 * (inputs.at(j) - targets.at(i));

            double costOverWeightRatio = a * Aj * dATOdZ;
            weightGradient.push_back(costOverWeightRatio);
        }
        weightGradients.push_back(weightGradient);
    }
    // newWeightsUpdate.push_back(weightGradients);
    newWeightsUpdate.insert(newWeightsUpdate.begin(), weightGradients);
    std::vector<double> biasGradients;
    for (int i=0; i < outputValues->size(); i++) {
        double dATOdZ = derivativeSigmoid(Zj.at(i)); // derivative A / derivative Z
        // double Aj = 2 * (level->levelNeuronOutputValue.at(i) - targets.at(i));
        double Aj = targets->at(i);

        double costOverWeightRatio = 1 * Aj * dATOdZ;
        biasGradients.push_back(costOverWeightRatio);
    }
    newBiasesUpdate.insert(newBiasesUpdate.begin(), biasGradients);

    // std::vector<double> nextLayerTarget;
    // for (int k=0; k < outputValues.size(); k++) {
    //     double nextNeuronValue;

    //     for (int i=0; i < inputs.size(); i++) {
    //         double dATOdZ = derivativeSigmoid(Zj.at(i)); // derivative A / derivative Z
            
    //         double weight = level->weights.at(i).at(k);
    //         // double Aj = 2 * (level->levelNeuronOutputValue.at(i) - targets.at(i));
    //         double Aj = targets.at(i);
    
    //         double costOverWeightRatio = weight * Aj * dATOdZ;
    //         nextNeuronValue += costOverWeightRatio;
    //     }
    //     nextLayerTarget.push_back(nextNeuronValue);
    // }

    std::vector<double> nextLayerTarget;
    for (int i=0; i < inputs->size(); i++) {
        double derivative;
        for (int j=0; j < outputValues->size(); j++) {
            double w = level->weights.at(j).at(i);
            double a  = derivativeSigmoid(Zj.at(j));
            double Co = targets->at(j);
            double v = w * a * Co;
            derivative += v;
        }
        nextLayerTarget.push_back(derivative);
    }
    // std::cout << nextLayerTarget.size() << " Q " << inputs.size() << std::endl;

    std::vector<double> weights;
    for (int i=0; i < outputValues->size(); i++) {
        for (int j=0; j < level->weights.at(i).size(); j++) {
            double newWeight = level->weights.at(i).at(j) + (*learningRate * weightGradients.at(i).at(j));
            level->weights.at(i).at(j) = newWeight;
        }

        double newBias = level->biases.at(i) + (*learningRate * biasGradients.at(i));
        // double newBias = biasGradients.at(i);
        level->biases.at(i) = newBias;

    }
    
    // return nextLayerTarget;
    return nextLayerTarget;
}

void NeuralNetwork::backPropogation(std::vector<double>* newTargets, std::vector<double>* input) {
    std::vector<double> targets;
    if (timesRun == 0) {
        newWeigths.clear();
        newBiases.clear();
        std::vector<std::vector<std::vector<double>>> x;
        std::vector<std::vector<double>> qz;
        for (int i=0; i < levels.size(); i++) {
            std::vector<std::vector<double>> y;
            for (int j=0; j < levels.at(i).weights.size(); j++) {
                std::vector<double> z;
                for (int k=0; k < levels.at(i).weights.at(j).size(); k++) {
                    z.push_back(0);
                }
                y.push_back(z);
            }
            x.push_back(y);
            std::vector<double> w;
            for (int j=0; j < levels.at(i).biases.size(); j++) { 
                w.push_back(0);
            }
            qz.push_back(w);
        }
        newWeigths = x;
        newBiases = qz;
    }

    timesRun += 1;
    newWeightsUpdate.clear();
    newBiasesUpdate.clear();
    for (int i=0; i < newTargets->size(); i++) {
        // targets.push_back(1 - newTargets.at(i));
        targets.push_back(newTargets->at(i));
    }
    feedForward(*input);
    double learningRate = 0.5;
    for (int i=levels.size()-1; -1 < i; i--) { // loop backwards trough te levels for backpropagation
        // std::cout << targets.at(0) << " in" << std::endl;
        // if (i == 0) {
        //     targets = propagate(input, levels.at(i).levelNeuronOutputValue, targets, &levels.at(i), learningRate);
        // } else {
        //     targets = propagate(levels.at(i-1).levelNeuronOutputValue, levels.at(i).levelNeuronOutputValue, targets, &levels.at(i), learningRate);
        // }
        // std::cout << "ja" << std::endl;
        std::vector<double>* targetsPtr = new std::vector<double>(targets);
        if (i == 0) {
            targets = propagate2(input, &levels.at(i).levelNeuronOutputValue, targetsPtr, &levels.at(i), &learningRate);
            // std::cout << "ja";
        } else if (i == levels.size()-1) {
            targets = propagate(&levels.at(i-1).levelNeuronOutputValue, &levels.at(i).levelNeuronOutputValue, targetsPtr, &levels.at(i), &learningRate);
            // std::cout << targets.size() << std::endl;
            // std::cout << "jna";
        } else {
            targets = propagate2(&levels.at(i-1).levelNeuronOutputValue, &levels.at(i).levelNeuronOutputValue, targetsPtr, &levels.at(i), &learningRate);
            // std::cout << targets.size() << std::endl;
            // std::cout << "jnweea";
        }
        delete targetsPtr;
        targetsPtr = NULL;

        // std::cout << targets.at(0) << std::endl;

        // for (int k=0; k < levels.at(i).levelOutputCount; k++) {
        //     for (int j=0; j < levels.at(i).levelInputCount; j++) {
        //         std::cout << "weight " << levels.at(i).weights.at(j).at(k) << " ";
        //     }
        //     std::cout << "bias " << levels.at(i).biases.at(k) << std::endl;
        // }
    }
    // std::cout << newWeigths.at(0).at(0).size();
    // for (int i=0; i < levels.size(); i++) {
    //     for (int j=0; j < newWeigths.at(i).size(); j++) {
    //         for (int k=0; k < levels.at(levels.size()-1-i).weights.at(j).size(); k++) {
    //             newWeigths.at(i).at(j).at(k) = newWeigths.at(i).at(j).at(k) + newWeightsUpdate.at(i).at(j).at(k);
    //         }
    //         std::cout << "ja " << levels.at(levels.size()-1-i).weights.size() << " NEE " << newWeigths.at(i).at(j).size() << " j " << j << " j " << newWeigths.size() << " " << levels.size()-1-i  << std::endl;

    //     }
    //     std::cout << "ja " << newWeigths.at(i).size() << " i "  << i << std::endl;
    // }    
    // std::cout << newWeigths.size() << "  " << newWeightsUpdate.size() << " " << levels.size() << std::endl;

    // // for (int i=levels.size()-1; 0 < i; i--) {
    // //     for (int j=0; j < newWeigths.size(); j++) {
    // //         newWeigths.at(i).at(j) = newWeigths.at(i).at(j) + newWeightsUpdate.at(i).at(j);
    // //     }
    // // }
    // if (timesRun >= 10) {
    //     timesRun = 0;
    //     for (int i=levels.size(); 0 < i; i--) {
    //         for (int j=0; j < newWeigths.size(); j++) {
    //             for (int k=0; k < newWeigths.at(j).size(); k++) {
    //                 levels.at(i).weights.at(j).at(k) = levels.at(i).weights.at(j).at(k) + learningRate * newWeightsUpdate.at(i).at(j).at(k);
    //             }
    //         }
    //     }
    // }
    for (int i=0; i < levels.size(); i++) {
        for (int j=0; j < levels.at(i).weights.size(); j++) {
            for (int k=0; k < levels.at(i).weights.at(j).size(); k++) {
                newWeigths.at(i).at(j).at(k) = newWeigths.at(i).at(j).at(k) + newWeightsUpdate.at(i).at(j).at(k);
            }
        }
        for (int j=0; j < levels.at(i).biases.size(); j++) {
            newBiases.at(i).at(j) = newBiases.at(i).at(j) +  newBiasesUpdate.at(i).at(j);
        }
        // std::cout << newBiases.at(i).size() << "  " << newBiasesUpdate.at(i).size() << " " << levels.at(i).biases.size() << std::endl; 
        // std::cout << "ja";
    }    
    // std::cout << newWeigths.size() << "  " << newWeightsUpdate.size() << " " << levels.size() << std::endl;

    // for (int i=levels.size()-1; 0 < i; i--) {
    //     for (int j=0; j < newWeigths.size(); j++) {
    //         newWeigths.at(i).at(j) = newWeigths.at(i).at(j) + newWeightsUpdate.at(i).at(j);
    //     }
    // }
    if (timesRun >= 10) {
        timesRun = 0;
        // for (int i=0; i < levels.size()-1; i++) {
        //     for (int j=0; j < levels.at(i).weights.size(); j++) {
        //         for (int k=0; k < levels.at(i).weights.at(j).size(); k++) {
        //             levels.at(i).weights.at(j).at(k) = levels.at(i).weights.at(j).at(k) + learningRate * newWeigths.at(i).at(j).at(k);
        //         }
        //     }
        // }
        // for (int i=0; i < levels.size()-1; i++) {
        //     for (int j=0; j < newBiases.at(i).size(); j++) {
        //         levels.at(i).biases.at(j) = levels.at(i).biases.at(j) + learningRate * newBiases.at(i).at(j); 
        //     }
        // }
    }
    // std::cout << std::endl;
    // std::cout << std::endl;
}

void NeuralNetwork::saveNeuralNetwork() {
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

void NeuralNetwork::loadNeuralNetwork(nlohmann::json networkData) {    
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

// int main() {
//     // srand(time(NULL));
//     NeuralNetwork nn({4, 9, 4});
//     std::vector<double> input = {1, 0.6, 0.5, 0.1};

//     nn.feedForward(input);
//     for (int j=0; j < nn.networkOutput.size(); j++) {
//         std::cout << nn.networkOutput.at(j) << " ";
//     }
//     std::cout << std::endl;
//     for (int i=0; i < 1000000; i++) {
//         nn.feedForward(input);
//         nn.backPropogation({1, 0, 0, 0.5}, input);
//         // std::cout << nn.levels.at(0).weights.at(0).at(0) << std::endl;
//     }
//     for (int j=0; j < nn.networkOutput.size(); j++) {
//         std::cout << nn.networkOutput.at(j) << " ";
//     }
//     std::cout << std::endl;




//     return 0;
// }