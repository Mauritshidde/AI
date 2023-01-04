#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "networkcode/nnLevel2.h"

int correct, notcorrect;

int argmax(std::vector<double> val){
    int highest = 0;
    for (int i=0; i < val.size(); i++) {
        if (val.at(i) > val.at(highest)) {
            highest = i;
        }
    }
    return highest;
}

int main() {
    std::vector<std::vector<std::vector<double>>> images;
    std::vector<int> imageValue;

    nlohmann::json trainingData;
    std::ifstream f("MNIST.json");
    nlohmann::json data = nlohmann::json::parse(f);
    f.close();
    trainingData = data;
    // std::cout << data["0"]["data"]["0"]["0"].get<double>();
    for (int i=0; i < 10000; i++) {
        std::vector<std::vector<double>> image;
        for (int j=0; j < 28; j++) {
            std::vector<double> rows;
            for (int k=0; k < 28; k++) {
                rows.push_back(data[std::to_string(i)]["data"][std::to_string(j)][std::to_string(k)].get<double>());
            }
            image.push_back(rows);
        }
        images.push_back(image);
        imageValue.push_back(data[std::to_string(i)]["value"].get<int>());
    }
    std::cout << "done loading images" << std::endl;

    // std::vector<double> input;
    // for (int i=0; i < 28; i++) {
    //     for (int j=0; j < 28; j++) {
    //         input.push_back(images.at(z).at(i).at(j));
    //     }
    // }

    srand(time(NULL));
    NeuralNetwork nn({784, 32, 32, 16, 10});
    // std::vector<double> input;
    for (int z=0; z < 9980; z++) {
        std::vector<double> input;
        for (int i=0; i < 28; i++) {
            for (int j=0; j < 28; j++) {
                input.push_back(images.at(z).at(i).at(j));
            }
        }
        
        nn.feedForward(input);
        // for (int j=0; j < nn.networkOutput.size(); j++) {
        //     std::cout << nn.networkOutput.at(j) << " ";
        // }
        // std::cout << std::endl;
        std::vector<double> target;
        for (int i=0; i < 10; i++) {
            if (i == imageValue.at(z)) {
                target.push_back(1);
                // std :: cout << i;
            } else {
                target.push_back(0);
            }
        }
        // for (int i=0; i < 10; i++) {
        //     std::cout << target.at(i) << " ";
        // }
        // std::cout << std::endl;
        std::vector<double>* targetPtr = new std::vector<double>(target);
        std::vector<double>* inputPtr = new std::vector<double>(input);

        for (int i=0; i < 1; i++) {
            nn.backPropogation(targetPtr, inputPtr);
            nn.feedForward(input);
            int gues = argmax(nn.networkOutput);
            if (target.at(gues) == 1) {
                correct++;
            } else {
                notcorrect++;
            }
            // std::cout << nn.levels.at(0).weights.at(0).at(0) << std::endl;
        }
        delete targetPtr;
        delete inputPtr;
        // for (int j=0; j < nn.networkOutput.size(); j++) {
        //     std::cout << nn.networkOutput.at(j) << " ";
        // }
    }
    std::cout << correct << " correct " << notcorrect << " notcorrect " << correct/1000 << " procent correct" << std::endl;
    correct = 0;
    notcorrect = 0;
    for (int z=9980; z < 10000; z++) { 
        std::vector<double> input;
        for (int i=0; i < 28; i++) {
            for (int j=0; j < 28; j++) {
                input.push_back(images.at(z).at(i).at(j));
            }
        }
        
        nn.feedForward(input);
        for (int j=0; j < nn.networkOutput.size(); j++) {
            std::cout << nn.networkOutput.at(j) << " ";
        }
        std::cout << " networkoutput before training  " << imageValue.at(z);
        std::cout << std::endl;
        std::vector<double> target;
        for (int i=0; i < 10; i++) {
            if (i == imageValue.at(z)) {
                target.push_back(1);
                // std :: cout << i;
            } else {
                target.push_back(0);
            }
        }
        std::vector<double>* targetPtr = new std::vector<double>(target);
        std::vector<double>* inputPtr = new std::vector<double>(input);
        for (int i=0; i < 1; i++) {
            nn.backPropogation(targetPtr, inputPtr);
            nn.feedForward(input);
            int gues = argmax(nn.networkOutput);
            if (target.at(gues) == 1) {
                correct++;
            } else {
                notcorrect++;
            }
        
        }
        delete targetPtr;
        delete inputPtr;
        for (int j=0; j < nn.networkOutput.size(); j++) {
            std::cout << nn.networkOutput.at(j) << " ";
        }
        std::cout << " network output after taringing " << imageValue.at(z);
        std::cout << std::endl;
        std::cout << std::endl;
    }
    std::cout << correct << " correct " << notcorrect << " notcorrect " << correct/1000 << " procent correct" << std::endl;

    // std::cout << std::endl;

    // for (int i=0; i < imageValue.size(); i++) {

    // }
}