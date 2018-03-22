EXE = Heat++
TEST_EXE = TestHeat++

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
OBJ_WITHOUT_MAIN = $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
TEST_OBJ = $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
BIN = $(wildcard $(BIN_DIR)/*.out)
TEST_BIN = $(wildcard $(TEST_BIN_DIR)/*.out)
LIB = -llapack -lblas -lboost_program_options
TEST_LIB = $(wildcard $(TEST_LIB_DIR)/*.a)

# CXX = g++
CXX = mpicxx
RUN = mpirun -np 2
CXXFLAGS += -std=c++11 -Wall -O2
TEST_CXXFLAGS += -pthread
INC = -Iinclude
TEST_INC = -Itest/include/

default: compile

all: compile

compile: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(BIN_DIR)/$@.out $(LIB)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

test: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(OBJ_WITHOUT_MAIN)
	$(CXX) $^ -o $(TEST_BIN_DIR)/$@.out $(TEST_LIB) $(LIB)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TEST_CXXFLAGS) $(TEST_INC) $(INC) -c $< -o $@

travis: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(OBJ_WITHOUT_MAIN)
	$(CXX) $^ -o $(TEST_BIN_DIR)/$@.out -lgtest $(LIB)

$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TEST_CXXFLAGS) $(INC) -c $< -o $@

debug: CXXFLAGS += -DDEBUG -g
debug: $(TEST_EXE)

.PHONY: c1
c1:
	$(BIN) -A 0.0 --left-height 1.0 --right-height 1.0 -L 2.0 -T 0.2 \
		   --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
		   --n-x 100 --n-y 50 \
		   --flux-location right --flux-value 2500.0 \
		   --temp-location left --temp-value 10.0

.PHONY: c2
c2:
	$(BIN) -A 0.0 --left-height 1.0 --right-height 1.0 -L 2.0 -T 0.2 \
		   --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
		   --n-x 10 --n-y 5 \
		   --flux-location top --flux-value 2500.0 \
		   --temp-location bottom --temp-value 10.0

.PHONY: c3
c3:
	$(BIN) -A 0.25 --left-height 1.0 --right-height 1.3 -L 3.0 -T 0.2 \
		   --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
		   --n-x 15 --n-y 8 \
		   --flux-location bottom --flux-value -5000.0 \
		   --temp-location left --temp-value -20.0

.PHONY: c1p
c1p:
	$(RUN) $(BIN) -A 0.0 --left-height 1.0 --right-height 1.0 -L 2.0 -T 0.2 \
		          --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
		          --n-x 100 --n-y 50 \
		          --flux-location right --flux-value 2500.0 \
		          --temp-location left --temp-value 10.0

.PHONY: c2p
c2p:
	$(RUN) $(BIN) -A 0.0 --left-height 1.0 --right-height 1.0 -L 2.0 -T 0.2 \
		          --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
		          --n-x 10 --n-y 5 \
		          --flux-location top --flux-value 2500.0 \
		          --temp-location bottom --temp-value 10.0

.PHONY: c3p
c3p:
	$(RUN) $(BIN) -A 0.25 --left-height 1.0 --right-height 1.3 -L 3.0 -T 0.2 \
		          --k-xx 250.0 --k-xy 0.0 --k-yy 250.0 \
		          --n-x 15 --n-y 8 \
		          --flux-location bottom --flux-value -5000.0 \
		          --temp-location left --temp-value -20.0

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(BIN)
	$(RM) $(TEST_OBJ)
	$(RM) $(TEST_BIN)
