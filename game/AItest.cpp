#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "networkcode/nnLevel2.h"

int main() {
    srand(time(NULL));
    NeuralNetwork nn({8, 12, 6, 6, 4});

    nn.feedForward({1, 0.5,1, 0.5,1, 0.5,1, 0.5});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    std::cout << std::endl;
    
    for (int i=0; i < 10000; i++) {
        std::vector<double> m = {0, 111, 0, 0};
        std::vector<double> n = {1, 0.5,1, 0.5,1, 0.5,1, 0.1};
        std::vector<double>* mn = new std::vector<double>(m);
        std::vector<double>* nm = new std::vector<double>(n);
        nn.backPropogation(mn, nm);
        delete mn;
        delete nm;

        // std::vector<double> m2 = {0, 0, 0, 1};
        // std::vector<double> n2 = {0, 0,1, 0,0, 0,0, 1};
        // std::vector<double>* mn2 = new std::vector<double>(m2);
        // std::vector<double>* nm2 = new std::vector<double>(n2);
        // nn.backPropogation(mn2, nm2);
        // delete mn2;
        // delete nm2;
    }
    nn.feedForward({1, 0.5,1, 0.5,1, 0.5,1, 0.5});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out ";
    }
    std::cout << std::endl;

    nn.feedForward({1, 0,0, 0,0, 1,1, 1});
    for (int i=0; i < nn.networkOutput.size(); i++) {
        std::cout << nn.networkOutput.at(i) << " out2 ";
    }
    std::cout << std::endl;

    return 0;
}