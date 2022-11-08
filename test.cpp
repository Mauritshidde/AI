#include <iostream>
#include <vector>
#include <cmath>


std::vector<double> Propagate(std::vector<double> input, double target, std::vector<double> weights) {
    double learningRate = 0.0001;
    double output = 1;
    for (int i=0; i < input.size(); i++) {
        output += input.at(i) * weights.at(i);
    }
    double dErrorTot = -(target-output);
    double dErrorout = dErrorTot;
    std::vector<double> dEoutDweigth;
    std::vector<double> dEtotDweigth;
    for (int i=0; i < input.size(); i++) {
        // dEoutDweigth.push_back(input.at(i));
        double val = dErrorTot * input.at(i);
        dEtotDweigth.push_back(val);
    }
    std::vector<double> newWeigths;
    for (int i=0; i < weights.size(); i++) {
        double val = weights.at(i) - (learningRate * dEtotDweigth.at(i));
        newWeigths.push_back(val);
    }
    std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x + " << newWeigths.at(1) << "y + " << newWeigths.at(2) << "z" << std::endl;
    // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x + " << newWeigths.at(1) << "y" << std::endl;
    // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x" << std::endl;

    return newWeigths;
}

int main() {
    std::vector<double> weights = {0.1, 0.5, 7};
    // std::vector<std::vector<double>> nWeights = {{0.1, 0.3}, {0.3, 0.5}};
    
    
    for (int i=0; i < 10; i++) {
        // std::vector<double> newWeigths;
        double target = 0.000001;
        double x = 40;
        std::vector<double> targets = {1, 0.01, 0.001, 0.00001, 0.0000001};
        std::vector<double> xs = {0, 40000, 50000, 80000, 100000};
        for (int j=0; j < targets.size(); j++) {
            std::vector<double> newWeigths;
            std::cout << xs.at(j);
            newWeigths = Propagate({xs.at(j) , pow(xs.at(j), 2), pow(xs.at(j), 3)}, targets.at(j), weights);
            weights = newWeigths;
        }
        // std::vector<std::vector<double>> newWeigths;


        // for (int k=0; k < nWeights.size(); k++) {
        //     std::vector<double> newWeigths;
        //     newWeigths = Propagate({1, 0.8}, -7, nWeights.at(k));
        //     for (int j=0; j < newWeigths.size(); j++) {
        //         nWeights.at(k).at(j) = newWeigths.at(j);
        //     }
        // }
    }

    return 0;
}