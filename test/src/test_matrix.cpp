#include "../include/gtest/gtest.h"
#include "../../include/matrix.h"

TEST (MatrixTest, EqualsZero) {
    EXPECT_EQ (0, matrix());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
