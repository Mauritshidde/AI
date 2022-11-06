#include <iostream>
#include <vector>
#include <cmath>


std::vector<double> Propagate(std::vector<double> input, double target, std::vector<double> weights) {
    double learningRate = 0.00001;
    double output;
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
    // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x + " << newWeigths.at(1) << "y + " << newWeigths.at(2) << "z" << std::endl;
    std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x + " << newWeigths.at(1) << "y" << std::endl;
    // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x" << std::endl;

    return newWeigths;
}

int main() {
    std::vector<double> weights = {0.1, 0.3};
    
    for (int i=0; i < 1000000; i++) {
        std::vector<double> newWeigths;
        newWeigths = Propagate({1, 0.8}, -7, weights);

        for (int j=0; j < newWeigths.size(); j++) {
            weights.at(j) = newWeigths.at(j);
        }
    }

    return 0;
}