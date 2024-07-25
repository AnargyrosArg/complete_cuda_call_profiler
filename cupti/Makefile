SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


CUPTI_SOURCE_FILES = $(wildcard $(SRC)/cupti/*.cpp)
CUPTI_TMP_SOURCE_FILES = $(CUPTI_SOURCE_FILES:$(SRC)/cupti/%=%)
CUPTI_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(CUPTI_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)

.PHONY: src clean

all: $(BUILD_DIR) libwrapper_cupti.so libcupti.so


libwrapper_cupti.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper_cupti.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations   -L${CUDA_HOME}/extras/CUPTI/lib64/ -lcupti_static -Wl,--export-dynamic

libcupti.so:  $(CUPTI_OBJ_FILES) $(BUILD_DIR)
	@g++ $(CUPTI_OBJ_FILES) -o libcupti.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)' -Wl,-soname,libcupti.so.11.7



$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include -I${CUDA_HOME}/extras/CUPTI/include -g -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cupti/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include -I${CUDA_HOME}/extras/CUPTI/include -g -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
