SRC = ./src
BUILD_DIR = ./build

SOURCE_FILES = $(wildcard $(SRC)/*.cpp)
TMP_SOURCE_FILES = $(SOURCE_FILES:$(SRC)/%=%)
OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(TMP_SOURCE_FILES:.cpp=.o))

CWD = $(shell pwd)

.PHONY: src

all: $(BUILD_DIR) libdlopen.so


libdlopen.so:  $(OBJ_FILES) 
	@g++ $(OBJ_FILES) -o libdlopen.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -Wl,-rpath,'$(CWD)'

#Compiles each source file into its object file individually 
$(BUILD_DIR)/%.o : $(SRC)/%.cpp 
	@g++ -O3 -I${CUDA_HOME}/include -g -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations  -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
