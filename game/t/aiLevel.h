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
    // inputs = new int[inputCount];
    // outputs = new int[outputCount];
    // biases = new int[outputCount];
    // for (int i=0; i < inputCount; i++) {
    //     std::vector<int> newVector;
    //     weights.push_back(newVector);
    // }
    randomize();
}
void Level::randomize() {
    for (int i=0; i < inputCount; i++) {
        // std:: cout << i << std::endl;
        std::vector<double> weights2;
        for (int j=0; j < outputCount; j++) {
            // weights.at(i).push_back(((rand() % 100)/100)*2-1);
            double v1 = rand() % 100; 
            double v2 = (v1/100)*2-1;
            weights2.push_back(v2);
        }
        
        weights.push_back(weights2);
        // std::cout << weights2.size() << " huehjw " << inputCount << " " << outputCount << std::endl;
    }
    
    // std::cout << weights.size() << " end" << std::endl;
    for (int i=0; i < outputCount; i++) {
        // biases[i] = ((rand() % 100)/100)*2-1;
        double v1 = rand() % 100; 
        double v2 = (v1/100)*2-1;
        biases.push_back(v2);
    }
}
std::vector<double> Level::feedForward(std::vector<double> givenInputs, Level level) {
    std::vector<int> inputs;
    std::vector<double> outputs;
    // std::cout << givenInputs.at(1) << "   dfghjkl" << std::endl;
    // for (int i=0; i < inputCount; i++) {
    //     // inputs[i] = givenInputs.at(i);
    //     inputs.push_back(givenInputs.at(i));
    //     std::cout << inputs.at(i) << " " << givenInputs.at(i) << " cgvuhijo;p" << std::endl;
    // }
    for (int i=0; i < inputCount; i++) {
        double sum = 0;
        for (int j=0; j < outputCount; j++) {
                // std::cout << weights.at(i).size() << std::endl;
            if (weights.at(i).size() == 0) {
                
            } else {
                // std::cout << weights.at(i).size() << std::endl;
                // std::cout << outputCount << "ja" << std::endl;
                // std::cout << weights.at(i).at(j) << std::endl;
                // std::cout << weights.at(i).at(j) << "Jasd" << std::endl;
                sum += givenInputs.at(i) * weights.at(i).at(j);
                // std::cout << sum << " xe " << weights.at(i).at(j) << " k " << givenInputs.at(i) << std::endl;
            }
        }
        if (sum > biases[i]) {
            // std::cout << biases[i] << " biases " << std::endl;
            outputs.push_back(1);
        } else {
            // std::cout << sum << " xe " << biases[i] << " k " << std::endl;
            outputs.push_back(0);
        }
    }
    return outputs;
}