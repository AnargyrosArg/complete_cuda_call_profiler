SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


RT_SOURCE_FILES = $(wildcard $(SRC)/cudart/*.cpp)
RT_TMP_SOURCE_FILES = $(RT_SOURCE_FILES:$(SRC)/cudart/%=%)
RT_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(RT_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)

EXTRA_FLAGS =
 
.PHONY: src clean

all: $(BUILD_DIR) libcudart.so


# libwrapper_cudart.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
#	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper_cudart.so -fPIC -shared -D_GNU_SOURCE -L${CUDA_HOME}/lib64 -lcudart_static -Wl,--export-dynamic

libcudart.so:  $(RT_OBJ_FILES) $(BUILD_DIR)
	@g++ $(RT_OBJ_FILES) -o libcudart.so -fPIC -shared -D_GNU_SOURCE -ldl -Wl,-rpath,'$(CWD)' -Wl,-soname,libcudart.so.11


#$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
#	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cudart/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
