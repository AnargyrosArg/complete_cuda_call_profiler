SRC = ./src
BUILD_DIR = ./build


WRAPPER_SOURCE_FILES = $(wildcard $(SRC)/wrapper/*.cpp)
TMP_SOURCE_FILES = $(WRAPPER_SOURCE_FILES:$(SRC)/wrapper/%=%)
WRAPPER_OBJ_FILES = $(addprefix $(BUILD_DIR)/wrapper_,$(TMP_SOURCE_FILES:.cpp=.o))


SOLVER_SOURCE_FILES = $(wildcard $(SRC)/cusolver/*.cpp)
SOLVER_TMP_SOURCE_FILES = $(SOLVER_SOURCE_FILES:$(SRC)/cusolver/%=%)
SOLVER_OBJ_FILES = $(addprefix $(BUILD_DIR)/,$(SOLVER_TMP_SOURCE_FILES:.cpp=.o))



CWD = $(shell pwd)

.PHONY: src clean

all: $(BUILD_DIR) libwrapper_cusolver.so libcusolver.so


libwrapper_cusolver.so:  $(WRAPPER_OBJ_FILES) $(BUILD_DIR)
	@g++ $(WRAPPER_OBJ_FILES) -o libwrapper_cusolver.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -L${CUDA_HOME}/lib64 -lcusolver_static -Wl,--export-dynamic

libcusolver.so:  $(SOLVER_OBJ_FILES) $(BUILD_DIR)
	@g++ $(SOLVER_OBJ_FILES) -o libcusolver.so -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -ldl -Wl,-rpath,'$(CWD)'


$(BUILD_DIR)/wrapper_%.o : $(SRC)/wrapper/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include -g -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@

$(BUILD_DIR)/%.o : $(SRC)/cusolver/%.cpp
	@g++ -O3 -I${CUDA_HOME}/include -g -fPIC -shared -D_GNU_SOURCE -Wno-deprecated -Wno-deprecated-declarations -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) *.so

#Rule to make sure build directory exists
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
