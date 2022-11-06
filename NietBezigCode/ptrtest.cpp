#include <iostream>
#include <vector>

#include <algorithm>
#include <sstream>
#include <iterator>

std::vector<double> tried;

void test(int ja) {
    std::cout << "After doing *ptr = 20, *ptr is "<< ja << std::endl;
}

bool checkPlacement(std::vector<std::vector<bool>>& board, int row, int column, int N) {
    for (int i = 0; i < column; i++) {
        if (board[row][i]) {
            return false;
        }
    }  
    for (int i = row, j = column; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]){
            return false;
        }
    }
    for (int i = row, j = column; j >= 0 && i < N; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }
    return true;
}

bool placeQueens(int inputs, int column, int possibleValues) {
    if (column >= inputs) {
        return true;
    }
    if (column == inputs-1) {
        for (int i = 0; i < possibleValues+1; i++) {

        }
    } else {
        bool ja = placeQueens(inputs, column+1, possibleValues);
    }
    return false;
}

void SetQtableVector(int inputs, int possibleValues) {
    std::vector<double> ja;
    for (int i=0; i < inputs; i++) {
        for (int j=0; j < possibleValues; j++) {
            ja.push_back(j);
        }
    }
}

int main() {
    std::vector<int> vecOfNums;
    for (int i=0; i < 8; i++) {
        for (int j=0; j < 10; j++) {
            vecOfNums.push_back(j);
        }
    }
    // A normal integer variable
    for (int i=0; i < 10000; i++) {
        // char* str = new char [30]; // Give str a memory address.

        // // delete [] str; // Remove the first comment marking in this line to correct.

        // str = new char [60]; /* Give str another memory address with
        //                                                     the first one gone forever.*/

        // delete [] str;
        double *ptr5 = new double(4);
        std::vector<double*> test;
        test.push_back(ptr5);
        // int* Var = new int(10);
        std::cout << *test.at(0) << "ja "<<  std::endl;
        delete ptr5;

        std::vector<int> v = {10,1,2,3,0,0,0,0};
        std::string delim = "|";
    
        std::stringstream ss;
        std::copy(v.begin(), v.end(),
                std::ostream_iterator<int>(ss, delim.c_str()));
        std::string testja = ss.str().substr(0, 2*v.size() - 1);
        std::cout << testja << std::endl;

        std::vector<std::string> vtr= {"Dog Rose", "Honeysuckle", "Enchanter's nightshade", "Columbine", "Kingcup", "Cornflower", "Water avens", "Forget-me-not"};

        std::vector<std::string>::iterator it = find(vtr.begin(), vtr.end(), "Cornflower");

        if (it == vtr.end()) {
            std::cout << "Flower was not found!" << std::endl;
        } else {
            std::cout<< "Flower found at index: " << it - vtr.begin() << std::endl;
        }
        
        // std::vector<int>::iterator it = std::find(vecOfNums.begin(), vecOfNums.end(), 1200);
        // if (it != vecOfNums.end()) {
        //     std::cout << "Element Found" << std::endl;
        // } else {
        //     std::cout << "Element Not Found" << std::endl;
        //     int index = std::distance(vecOfNums.begin(), it);
        //     std::cout << vecOfNums.at(index) << " " << index << std::endl;
        // }
        // // A pointer variable that holds address of var.
        // // int *ptr = Var;
    
        // // This line prints value at address stored in ptr.
        // // Value stored is value of variable "var"
        // // std::cout << "Value of Var = "<< *ptr << std::endl;
    
        // // The output of this line may be different in different
        // // runs even on same machine.
        // // std::cout << "Address of Var = " <<  ptr << std::endl;
    
        // // We can also use ptr as lvalue (Left hand
        // // side of assignment)
        // *Var = 20; // Value at address is now 20
        // test(*Var);
    
        // // This prints 20
        // std::cout << "After doing *ptr = 20, *ptr is "<< *Var<<"  "<<Var<< std::endl;

    }
 
    return 0;
}