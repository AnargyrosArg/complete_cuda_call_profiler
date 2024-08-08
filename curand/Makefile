SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


SPARSE_SOURCE_FILES = $(wildcard $(SRC)/curand/*.cpp)
SPARSE_TMP_SOURCE_FILES = $(SPARSE_SOURCE_FILES:$(SRC)/curand/%=%)
SPARSE_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(SPARSE_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)



.PHONY: src clean

all: $(BUILD_DIR) libwrapper_curand.so libcurand.so


libwrapper_curand.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper_curand.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -L${CUDA_HOME}/lib64 -lcurand_static -Wl,--export-dynamic

libcurand.so:  $(SPARSE_OBJ_FILES) $(BUILD_DIR)
	@g++ $(SPARSE_OBJ_FILES) -o libcurand.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)' -Wl,-soname,libcurand.so.10


$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/curand/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
