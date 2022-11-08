#include <iostream>
#include <vector>
#include <cmath>


std::vector<double> Propagate(std::vector<double> input, double target, std::vector<std::vector<double>> weights) {
    std::vector<std::vector<double>> weightError;

    // std::vector<dou
    for (int i=0; i < input.size(); i++) {
        for (int j=0; j < weights.at(i).size(); j++) {
            
            
        }
    }

    for (int i=0; i < input.size(); i++) {
        for (int j=0; j < weights.at(i).size(); j++) {
            double x;
            double reverseSigmoid = (1 / (1+exp(-x))) * (1-1/(1+exp(-x)));
            weightError.at(i).push_back(reverseSigmoid);
        }
    }
    
    
    
    // double learningRate = 0.0001;
    // double output;
    // for (int i=0; i < input.size(); i++) {
    //     output += input.at(i) * weights.at(i);
    // }
    // double dErrorTot = -(target-output);
    // double dErrorout = dErrorTot;
    // std::vector<double> dEoutDweigth;
    // std::vector<double> dEtotDweigth;
    // for (int i=0; i < input.size(); i++) {
    //     // dEoutDweigth.push_back(input.at(i));
    //     double val = dErrorTot * input.at(i);
    //     dEtotDweigth.push_back(val);
    // }
    // std::vector<double> newWeigths;
    // for (int i=0; i < weights.size(); i++) {
    //     double val = weights.at(i) - (learningRate * dEtotDweigth.at(i));
    //     newWeigths.push_back(val);
    // }
    // // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x + " << newWeigths.at(1) << "y + " << newWeigths.at(2) << "z" << std::endl;
    // // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x + " << newWeigths.at(1) << "y" << std::endl;
    // // std::cout << "f(x,y,z) = " << newWeigths.at(0) << "x" << std::endl;

    return newWeigths;
}

void Backpropagation(std::vector<double> levels) {
    for (int i=levels.size()-1; i >= 0; i--) {
        // levels.at(i);
        if (i == 0) {
            
        }
        std::cout << "ja" << std::endl;
    }
}

void nnBackpropagation() {

}

int main() {
    std::vector<double> weights = {0.1, 0.3};
    std::vector<std::vector<double>> nWeights = {{0.3, 0.6}, {0.4, 0.7}};
    std::vector<double> target = {1, 0};
    
    for (int i=0; i < 1000000; i++) {
        // std::vector<double> newWeigths;
        // newWeigths = Propagate({1, 0.8}, -7, weights);
        // std::vector<std::vector<double>> newWeigths;
        std::vector<std::vector<double>> newWeigths;

        for (int k=0; k < nWeights.size(); k++) {
            newWeigths.push_back(Propagate({1, 0.5}, target.at(k), nWeights.at(k)));
        }
        for (int j=0; j < newWeigths.size(); j++) {
            nWeights.at(j) = newWeigths.at(j);
        }
    }
    std::cout << "f(x,y,z) = " << nWeights.at(0).at(0) << "x + " << nWeights.at(0).at(1) << "y" << std::endl;
    std::cout << "f(x,y,z) = " << nWeights.at(1).at(0) << "x + " << nWeights.at(1).at(1) << "y" << std::endl;
    Backpropagation({1,2,3});
    return 0;
}