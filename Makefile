EXE = HeatConduction

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
BIN = $(wildcard $(BIN_DIR)/*.out)

CXX = g++
CXXFLAGS += -Wall -O2 -Iinclude

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(BIN_DIR)/$@.out

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)
