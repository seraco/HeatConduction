EXE = HeatConduction
TEST_EXE = TestHeatConduction

SRC_DIR = src
TEST_SRC_DIR = test/src
OBJ_DIR = obj
TEST_OBJ_DIR = test/obj
BIN_DIR = bin
TEST_BIN_DIR = test/bin
TEST_LIB_DIR = test/lib

SRC = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
BIN = $(wildcard $(BIN_DIR)/*.out)
TEST_BIN = $(wildcard $(TEST_BIN_DIR)/*.out)
TEST_LIB = $(wildcard $(TEST_LIB_DIR)/*.a)

CXX = g++
CXXFLAGS += -Wall -O2
TEST_CXXFLAGS += -pthread
INC = -Iinclude
TEST_INC = -Itest/include

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(BIN_DIR)/$@.out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

test: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(OBJ)
	$(CXX) $^ -o $(TEST_BIN_DIR)/$@.out $(TEST_LIB)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TEST_CXXFLAGS) $(TEST_INC) $(INC) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)
	$(RM) $(TEST_OBJ)
	$(RM) $(TEST_BIN)
