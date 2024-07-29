SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


SPARSE_SOURCE_FILES = $(wildcard $(SRC)/cusparse/*.cpp)
SPARSE_TMP_SOURCE_FILES = $(SPARSE_SOURCE_FILES:$(SRC)/cusparse/%=%)
SPARSE_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(SPARSE_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)

EXTRA_FLAGS = 

.PHONY: src clean

all: $(BUILD_DIR) libwrapper_cusparse.so libcusparse.so


libwrapper_cusparse.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper_cusparse.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -L${CUDA_HOME}/lib64 -lcusparse_static -Wl,--export-dynamic

libcusparse.so:  $(SPARSE_OBJ_FILES) $(BUILD_DIR)
	@g++ $(SPARSE_OBJ_FILES) -o libcusparse.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)/' -Wl,-soname,libcusparse.so.11


$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cusparse/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include $(EXTRA_FLAGS) -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
