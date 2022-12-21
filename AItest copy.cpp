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
    std::vector<std::vector<std::vector<double>>> images;
    std::vector<int> imageValue;

    nlohmann::json trainingData;
    std::ifstream f("MNIST.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    trainingData = data;
    std::vector<std::vector<double>> image;
    for (int j=0; j < 28; j++) {
        std::vector<double> rows;
        for (int k=0; k < 28; k++) {
            rows.push_back(data[std::to_string(0)]["data"][std::to_string(j)][std::to_string(k)].get<double>());
        }
        image.push_back(rows);
    }
    images.push_back(image);
    imageValue.push_back(data[std::to_string(0)]["value"].get<int>());
    std::cout << imageValue.at(0) << std::endl;

    std::vector<double> input;
    for (int i=0; i < 28; i++) {
        for (int j=0; j < 28; j++) {
            input.push_back(images.at(0).at(i).at(j));
        }
    }

    NeuralNetwork nn({784, 2, 2, 10});
    nn.feedForward(input);
    for (int i=0; i < nn.networkOutput.size(); i++) {
        // std::cout << nn.networkOutput.at(i) << " out ";
    }
    nn.feedForward(input);
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
        std::vector<double> m = {0, 0, 0, 0, 0 ,1, 0 ,0 ,0,0};
        std::vector<double> n = input;
        std::vector<double>* mn = new std::vector<double>(m);
        std::vector<double>* nm = new std::vector<double>(n);
        nn.backPropogation(mn, nm);
        // nn.backPropogation({1, 0, 0, 0}, {0,0.8,0.1, 1, 0.5,0.9,0.9, 0, 0,0.3,0.1, 0.2});
        delete mn;
        delete nm;
    }
    nn.feedForward(input);
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    std::cout << std::endl;
    for (int i=0; i < 2; i++) {
        std::cout << nn.networkOutput.at(i) << " network output ";
    }
    std::cout << std::endl;
    std::cout << nn.levels.at(1).networkNetValues.at(0) << " net " << nn.levels.at(1).networkNetValues.at(1) <<  " net " << nn.levels.at(1).levelNeuronOutputValue.at(0) <<  " out "<< nn.levels.at(1).levelNeuronOutputValue.at(1) << " out ";
    std::cout << std::endl;
    for (int i=0; i < nn.levels.at(1).weights.size(); i++) {
        std::cout << nn.levels.at(1).weights.at(i).at(0) << " Ww " << nn.levels.at(1).weights.at(i).at(1) << " " << std::endl;
    }

    std::cout << nn.levels.at(0).levelNeuronOutputValue.at(0) << " input " << nn.levels.at(0).levelNeuronOutputValue.at(1) << std::endl;
    
    

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