SRC = ./src
BUILD_DIR = ./build


SOURCE_FILES = $(wildcard $(SRC)/cuda/*.cpp)
TMP_SOURCE_FILES = $(SOURCE_FILES:$(SRC)/cuda/%=%)
OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)



.PHONY: src

all: $(BUILD_DIR) libcuda_intercept.so


libcuda_intercept.so:  $(OBJ_FILES) 
	@g++ $(OBJ_FILES) -o libcuda_intercept.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -Wl,-rpath,'$(CWD)'

#Compiles each source file into its object file individually 
$(BUILD_DIR)/%.o : $(SRC)/cuda/%.cpp 
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations  -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
