#include <iostream>
#include <vector>
#include <cmath>

void gradientError(double target, double input, std::vector<double> weights) {
    double error, current;
    double output = input;
    for (int i=0; i < 2; i++) {
        output = output * weights.at(i);
    }
    error = 0.5 * pow((target - output), 2);
    std::cout << error << " " << output << std::endl;
}

void gradientDescent() {

}

void backPropegation() {
      
}

int main() {
    gradientError(5, 0.8, {0.05, 0.9});

    return 0;
}