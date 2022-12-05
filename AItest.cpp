#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "nnLevel2.h"

int main() {
    // NeuralNetwork nn({5, 45, 72, 1, 9});

    // for (int i=0; i < nn.levels.size(); i++) {
    //     for (int j=0; j < nn.levels.at(i).weights.size(); j++) {
    //         for (int k=0; k < nn.levels.at(i).weights.at(j).size(); k++) {
    //             std::cout << nn.levels.at(i).weights.at(j).at(k) << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout <<  " out " << std::endl;
    //     std::cout << std::endl;
    // }
    
    // nn.backPropogation({1, 0.4, 0.3, 0.9, 0}, {0,0,1});
    NeuralNetwork nn({4, 5, 3, 4});
    nn.feedForward({1,0.4,0.7, 0});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    for (int i=0; i < nn.levels.size(); i++) {
        for (int j=0; j < nn.levels.at(i).weights.size(); j++) {
            for (int k=0; k < nn.levels.at(i).weights.at(j).size(); k++) {
                std::cout << nn.levels.at(i).weights.at(j).at(k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout <<  " out " << std::endl;
        std::cout << std::endl;
    }
    for (int i=0; i < 1; i++) {
        nn.backPropogation({0, 1, 0, 1}, {1,0.4,0.7, 0});

    }
    nn.feedForward({1,0.4,0.7, 0});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    std::cout << std::endl;
    for (int i=0; i < nn.levels.at(1).networkNetValues.size(); i++) {
        std::cout << nn.levels.at(1).networkNetValues.at(i) << " net ";
    }
    std::cout << std::endl;
    for (int i=0; i < nn.levels.at(0).levelNeuronOutputValue.size(); i++) {
        std::cout << nn.levels.at(0).levelNeuronOutputValue.at(i) << " inin ";
    }
    std::cout << std::endl;
    return 0;
}