SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


BLAS_SOURCE_FILES = $(wildcard $(SRC)/cublas/*.cpp)
BLAS_TMP_SOURCE_FILES = $(BLAS_SOURCE_FILES:$(SRC)/cublas/%=%)
BLAS_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(BLAS_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)

EXTRA_FLAGS = 
.PHONY: src clean

all: $(BUILD_DIR) libwrapper.so libcublas.so


libwrapper.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -L${CUDA_HOME}/lib64 -lcublas_static -lcublasLt_static -Wl,--export-dynamic

libcublas.so:  $(BLAS_OBJ_FILES) $(BUILD_DIR)
	@g++ $(BLAS_OBJ_FILES) -o libcublas.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)' -Wl,-soname,libcublas.so.11


$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp 
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cublas/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
