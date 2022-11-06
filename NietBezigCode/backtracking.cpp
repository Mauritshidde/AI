#include <vector>
#include <iostream>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>

std::vector<int> current;
std::vector<std::string> QtableIndex;
std::vector<std::vector<double>> Qtable;
int maxValue = 7;



void checkIfvalueIn(std::string value) {
    std::vector<std::string>::iterator it = find(QtableIndex.begin(), QtableIndex.end(), value);

    if (it == QtableIndex.end()) {
        std::cout << "Flower was not found!" << std::endl;
    } else {
        std::cout<< "Flower found at index: " << it - QtableIndex.begin() << std::endl;
    }
    std::vector<double> newVec = {0, 0, 0, 0};
    Qtable.push_back(newVec);
}

void intToString(std::vector<int> v) {

    std::string delim = "|";

    std::stringstream ss;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, delim.c_str()));
    std::string testja = ss.str().substr(0, 2*v.size() - 1);
    std::cout << testja << std::endl;
    QtableIndex.push_back(testja);
}

bool bactrack(int currentRay) {
    if (currentRay == 9) {
        for (int i=0; i < 8; i++) {
            // std::cout << i <<std::endl;
            current.push_back(i);
            // std::cout << current.size() << std::endl;
            intToString(current);
            current.pop_back();
        }
        bactrack(currentRay-1);
    } else {
        // std::cout << " ja " << std::endl;
        if (current.size()-1 == currentRay) {
            int value = current.at(currentRay);
            if (value == maxValue) {
                if (currentRay == 0) {
                    return true;
                } else {
                    current.pop_back();
                    bactrack(currentRay-1);
                }
            } else {
                current.pop_back();
                current.push_back(value+1);
                bactrack(currentRay+1);
            }
        } else {
            // std::cout << " ja " << std::endl;

            current.push_back(0);
            bactrack(currentRay+1);
        }
    }
    return false;
} 


int main() {
    // std::vector<int> current;

    bactrack(0);
    
    checkIfvalueIn("2|2|3|1");
    for (int i=0; i < 4; i++) {
        std::cout << Qtable.at(0).at(i) << "   ";
    }
    
    
    
    return 0;
}