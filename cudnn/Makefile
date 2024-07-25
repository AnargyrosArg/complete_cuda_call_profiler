SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


CUDNN_SOURCE_FILES = $(wildcard $(SRC)/cudnn/*.cpp)
CUDNN_TMP_SOURCE_FILES = $(CUDNN_SOURCE_FILES:$(SRC)/cudnn/%=%)
CUDNN_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(CUDNN_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)

.PHONY: src clean

all:$(BUILD_DIR) libwrapper_cudnn.so libcudnn.so


libwrapper_cudnn.so:  $(WRAPPER_OBJ_FILES) 
	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper_cudnn.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -L${CUDA_HOME}/lib64 -lcudnn_static -lculibos -Wl,--export-dynamic

libcudnn.so:  $(CUDNN_OBJ_FILES) $(BUILD_DIR)
	@g++ $(CUDNN_OBJ_FILES) -o libcudnn.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)' 


$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include -g -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cudnn/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include -g -fPIC -shared -Wno-deprecated -Wno-deprecated-declarations -D_GNU_SOURCE -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
