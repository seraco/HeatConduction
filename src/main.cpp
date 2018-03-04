#include <iostream>

#include "../include/matrix.h"

int main(int argc, char const *argv[]) {
    CMatrix<int> A(4, 4, 2);
    std::cout << A(3, 3) << std::endl;
    return 0;
}
