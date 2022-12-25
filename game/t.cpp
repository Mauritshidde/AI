#include <iostream>

void test(int x=4, int y=5) {
    std::cout << x << "  " << y << std::endl;
}


int main() {

    
    test(3, 4);
    
    return 0;
}