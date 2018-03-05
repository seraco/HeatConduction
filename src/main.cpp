#include <iostream>

#include "../include/matrix.h"

int main(int argc, char const *argv[]) {
    CMatrix<int> A(4, 4, 2);
    CMatrix<int> B = CMatrix<int>(A);
    CMatrix<int> C;
    CMatrix<int> D;
    CMatrix<int> E(4, 1, 2);
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
