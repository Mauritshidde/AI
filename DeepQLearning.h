#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <string>
#include <cstdlib>
#include <iomanip>

#include <malloc.h>
#include "Qnn.h"

class DeepQLearning {
    public:
        DeepQLearning();
        ~DeepQLearning();
        int makeDecision();
        void Reward();
        void saveQtable();
        void SetEpsilon(float newepsilon);
        void UpdateQtable(std::vector<float> *state);
    private:
        void SetNN();
        double epsilon = 1;
        float reward;
        int action = 0;
        int action1, action2, action3, action4;
        std::vector<int> previousActions;
        NeuralNetwork* network = new NeuralNetwork({3,4,6,3});
        
};

DeepQLearning::DeepQLearning() {
    std::ifstream f("Qtable.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    // malloc_trim(0);
    // delete data;
    // data = NULL;
    
}

DeepQLearning::~DeepQLearning() {
    delete network;
}

void DeepQLearning::UpdateQtable(std::vector<float>* state) {

}

void DeepQLearning::Reward() {
}

void DeepQLearning::saveQtable() {
    // std::ofstream testfile;
    // testfile.open("Qtable.json");
    // testfile << Qtable;
    // testfile.close();
}   

void DeepQLearning::SetEpsilon(float newepsilon) {
    epsilon = newepsilon;
}
