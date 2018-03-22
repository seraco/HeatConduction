#include "gtest/gtest.h"
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
