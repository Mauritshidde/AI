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
    srand(time(NULL));
    NeuralNetwork nn({8, 30,30,15, 6, 4});
    for (int i=0; i < nn.levels.at(nn.levels.size()-1).weights.size(); i++) {
        // std::cout << nn.levels.at(nn.levels.size()-1).weights.at(i).at(0) << " Ww " << nn.levels.at(nn.levels.size()-1).weights.at(i).at(1) << " " << nn.levels.at(nn.levels.size()-1).weights.at(i).at(2) << " " << std::endl;
    }
    nn.feedForward({1, 0.5,1, 0.5,1, 0.5,1, 0.5});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        // std::cout << nn.networkOutput.at(i) << " out ";
    }
    nn.feedForward({1, 0.5,1, 0.5,1, 0.5,1, 0.5});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    std::cout << std::endl;
    for (int i=0; i < nn.levels.size(); i++) {
        for (int j=0; j < nn.levels.at(i).weights.size(); j++) {
            for (int k=0; k < nn.levels.at(i).weights.at(j).size(); k++) {
                // std::cout << nn.levels.at(i).weights.at(j).at(k) << " ";
            }
            // std::cout << std::endl;
        }
        // std::cout <<  " out " << std::endl;
        // std::cout << std::endl;
    }
    for (int i=0; i < 100000; i++) {
        std::vector<double> m = {0, 1, 0, 0};
        std::vector<double> n = {1, 0.5,1, 0.5,1, 0.5,1, 0.5};
        std::vector<double>* mn = new std::vector<double>(m);
        std::vector<double>* nm = new std::vector<double>(n);
        nn.backPropogation(mn, nm);
        // nn.backPropogation({1, 0, 0, 0}, {0,0.8,0.1, 1, 0.5,0.9,0.9, 0, 0,0.3,0.1, 0.2});
        delete mn;
        delete nm;
    }
    nn.feedForward({1, 0.5,1, 0.5,1, 0.5,1, 0.5});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    std::cout << std::endl;
    // for (int i=0; i < 2; i++) {
    //     std::cout << nn.networkOutput.at(i) << " network output ";
    // }
    // std::cout << std::endl;
    // std::cout << nn.levels.at(nn.levels.size()-1).networkNetValues.at(0) << " net " << nn.levels.at(nn.levels.size()-1).networkNetValues.at(1) <<  " net " << nn.levels.at(nn.levels.size()-1).levelNeuronOutputValue.at(0) <<  " out "<< nn.levels.at(nn.levels.size()-1).levelNeuronOutputValue.at(1) << " out ";
    // std::cout << std::endl;
    // for (int i=0; i < nn.levels.at(nn.levels.size()-1).weights.size(); i++) {
    //     std::cout << nn.levels.at(nn.levels.size()-1).weights.at(i).at(0) << " Ww " << nn.levels.at(nn.levels.size()-1).weights.at(i).at(1) << " " << nn.levels.at(nn.levels.size()-1).weights.at(i).at(2) << " " << std::endl;
    // }

    // std::cout << nn.levels.at(nn.levels.size()-2).levelNeuronOutputValue.at(0) << " input " << nn.levels.at(nn.levels.size()-2).levelNeuronOutputValue.at(1) << std::endl;
    
    

    // nn.feedForward({0,0.8,0.1, 1});
    // for (int i=0; i < nn.networkOutput.size(); i++) {
    //     std::cout << nn.networkOutput.at(i) << " out ";
    // }
    // std::cout << std::endl;
    // for (int i=0; i < nn.levels.at(1).networkNetValues.size(); i++) {
    //     std::cout << nn.levels.at(1).networkNetValues.at(i) << " net ";
    // }
    // std::cout << std::endl;
    // for (int i=0; i < nn.levels.at(0).levelNeuronOutputValue.size(); i++) {
    //     std::cout << nn.levels.at(0).levelNeuronOutputValue.at(i) << " inin ";
    // }
    // std::cout << std::endl;
    return 0;
}