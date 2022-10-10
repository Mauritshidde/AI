#include <iostream>
#include <vector>

void test(int ja) {
    std::cout << "After doing *ptr = 20, *ptr is "<< ja << std::endl;
}

int main()
{
    // A normal integer variable
    for (int i=0; i < 100000000000; i++) {
        char* str = new char [30]; // Give str a memory address.

        // delete [] str; // Remove the first comment marking in this line to correct.

        str = new char [60]; /* Give str another memory address with
                                                            the first one gone forever.*/

        delete [] str;
        // int* Var = new int(10);
    
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