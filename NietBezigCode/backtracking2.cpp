#include <vector>
#include <iostream>
#include <ostream>
#include <iterator>
#include <sstream>
#include <algorithm>

std::vector<int> current;
std::vector<std::string> QtableIndex;
std::vector<std::vector<double>> Qtable;
int maxValue = 10;



void checkIfvalueIn(std::string value) {
    std::vector<std::string>::iterator it = find(QtableIndex.begin(), QtableIndex.end(), value);

    if (it == QtableIndex.end()) {
        std::cout << "Flower was not found!" << "\n";
    } else {
        std::cout<< "Flower found at index: " << it - QtableIndex.begin() << "\n";
    }
    
}

void intToString(std::vector<int> v) {

    std::string delim = "|";

    std::stringstream ss;
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, delim.c_str()));
    std::string testja = ss.str().substr(0, 2*v.size() - 1);
    std::vector<double> newVec = {0, 0, 0, 0};
    Qtable.push_back(newVec);
    std::cout << testja << "  " << Qtable.size() << "\n";
    QtableIndex.push_back(testja);
}

bool bactrack(int currentRay) {
    bool door = true;
    while (door) {
        if (currentRay == 7) {
            for (int i=0; i < 11; i++) {
                // std::cout << i <<"\n";
                current.push_back(i);
                // std::cout << current.size() << "\n";
                intToString(current);
                current.pop_back();
            }
            currentRay--;
        } else {
            // std::cout << " ja " << "\n";
            if (current.size()-1 == currentRay) {
                int value = current.at(currentRay);
                if (value == maxValue) {
                    if (currentRay == 0) {
                        door = false;
                    } else {
                        current.pop_back();
                        currentRay--;
                    }
                } else {
                    current.pop_back();
                    current.push_back(value+1);
                    currentRay++;
                }
            } else {
                // std::cout << " ja " << "\n";

                current.push_back(0);
                currentRay++;
            }
        }

    }
    return true;
} 


int main() {
    // std::vector<int> current;

    bactrack(0);
    
    checkIfvalueIn("0|0|0|0|5|0|5|7|7|7");
    for (int i=0; i < 4; i++) {
        std::cout << Qtable.at(0).at(i) << "   ";
    }
    
    
    
    return 0;
}