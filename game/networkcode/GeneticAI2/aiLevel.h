#include <vector>
#include <cstdlib>

class Level {
    public:
        Level(int incount, int outcount);
        std::vector<double> feedForward(std::vector<double> givenInputs, Level level);
        std::vector<double> biases;
        std::vector<std::vector<double>> weights;
    private:
        void randomize();
        int inputCount, outputCount;

};

Level::Level(int incount, int outcount) {
    inputCount = incount;
    outputCount = outcount;
    randomize();
}

void Level::randomize() {
    for (int i=0; i < inputCount; i++) {
        std::vector<double> weights2;

        for (int j=0; j < outputCount; j++) {
            double v1 = rand() % 100; 
            double v2 = (v1/100)*2-1;
            weights2.push_back(v2);
        }
        weights.push_back(weights2);
    }

    for (int i=0; i < outputCount; i++) {
        double v1 = rand() % 100; 
        double v2 = (v1/100)*2-1;
        biases.push_back(v2);
    }
}

std::vector<double> Level::feedForward(std::vector<double> givenInputs, Level level) {
    std::vector<int> inputs;
    std::vector<double> outputs;

    for (int i=0; i < inputCount; i++) {
        double sum = 0;
        for (int j=0; j < outputCount; j++) {
            if (weights.at(i).size() == 0) {
                
            } else {
                sum += givenInputs.at(i) * weights.at(i).at(j);
            }
        }

        if (sum > biases[i]) {
            outputs.push_back(1);
        } else {
            outputs.push_back(0);
        }
    }
    return outputs;
}