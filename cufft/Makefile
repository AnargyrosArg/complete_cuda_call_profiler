SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


CUFFT_SOURCE_FILES = $(wildcard $(SRC)/cufft/*.cpp)
CUFFT_TMP_SOURCE_FILES = $(CUFFT_SOURCE_FILES:$(SRC)/cufft/%=%)
CUFFT_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(CUFFT_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)



.PHONY: src clean

all: $(BUILD_DIR) libwrapper_cufft.so libcufft.so


libwrapper_cufft.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
	@nvcc $(WRAPPER_OBJ_FILES) -o libwrapper_cufft.so --shared -L$(CUDA_HOME)/lib64 -lcufft_static -lculibos 

libcufft.so:  $(CUFFT_OBJ_FILES) $(BUILD_DIR)
	@g++ $(CUFFT_OBJ_FILES) -o libcufft.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)' -Wl,-soname,libcufft.so.10


$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cufft/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
