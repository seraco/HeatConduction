#include <iostream>

#include "../include/CMatrix.h"

int main(int argc, char const *argv[]) {
    CMatrix A(4, 4, 2);
    CMatrix B = CMatrix(A);
    CMatrix C;
    CMatrix D;
    CMatrix E(4, 1, 2);
    A += B;
    B -= A;
    C = A + B;
    D = B - A;
    A.printMtx();
    B.printMtx();
    C.printMtx();
    D.printMtx();
    E.printMtx();
    return 0;
}
