#include <iostream>
#include "S_Vector.h"
#include <vector>
#include <string>

int main() {
    std::cout << "Waiting for update." << std::endl;
    S_Vector<int> i_test1;
    S_Vector<int> i_test2(5);
    S_Vector<std::string> i_test3(5,"initial value");

    // Waiting for update.
    return 0;
}
