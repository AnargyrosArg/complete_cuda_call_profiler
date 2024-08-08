CWD = $(shell pwd)
EXTRA_FLAGS = -DPRINT_TRACE
export EXTRA_FLAGS

all: lib_dir dlopen_interposer cudart cuda cublas cublasLt cufft cupti curand cusolver cusparse cudnn


lib_dir:
	mkdir -p ./lib

dlopen_interposer: lib_dir
	cd dlopen_interposer 		&& make -j
	ln -fs $(CWD)/dlopen_interposer/libdlopen.so ./lib/libdlopen.so

cudart:	lib_dir
	cd ./cudart && make -j
	ln -fs $(CWD)/cudart/libcudart.so ./lib/libcudart.so
#	ln -fs $(CWD)/cudart/libwrapper.so ./lib/libwrapper_cudart.so


cuda : lib_dir	
	cd ./cuda && make -j
	ln -fs $(CWD)/cuda/libcuda_intercept.so ./lib/libcuda_intercept.so


cublas: lib_dir
	cd ./cublas && make -j
	ln -fs $(CWD)/cublas/libcublas.so ./lib/libcublas.so
	ln -fs $(CWD)/cublas/libwrapper.so ./lib/libwrapper.so

cublasLt: lib_dir
	cd ./cublasLt && make -j
	ln -fs $(CWD)/cublasLt/libcublasLt.so ./lib/libcublasLt.so
	ln -fs $(CWD)/cublasLt/libwrapper_cublasLt.so ./lib/libwrapper_cublasLt.so


cufft: lib_dir
	cd ./cufft && make -j
	ln -fs $(CWD)/cufft/libcufft.so ./lib/libcufft.so
	ln -fs $(CWD)/cufft/libwrapper_cufft.so ./lib/libwrapper_cufft.so

cupti: lib_dir
	cd ./cupti && make -j
	ln -fs $(CWD)/cupti/libcupti.so ./lib/libcupti.so
	ln -fs $(CWD)/cupti/libwrapper_cupti.so ./lib/libwrapper_cupti.so

curand: lib_dir
	cd ./curand && make -j
	ln -fs $(CWD)/curand/libcurand.so ./lib/libcurand.so
	ln -fs $(CWD)/curand/libwrapper_curand.so ./lib/libwrapper_curand.so

cusolver: lib_dir
	cd ./cusolver && make -j
	ln -fs $(CWD)/cusolver/libcusolver.so ./lib/libcusolver.so
	ln -fs $(CWD)/cusolver/libwrapper_cusolver.so ./lib/libwrapper_cusolver.so

cusparse: lib_dir
	cd ./cusparse && make -j
	ln -fs $(CWD)/cusparse/libcusparse.so ./lib/libcusparse.so
	ln -fs $(CWD)/cusparse/libwrapper_cusparse.so ./lib/libwrapper_cusparse.so

cudnn: lib_dir
	cd ./cudnn && make -j
	ln -fs $(CWD)/cudnn/libcudnn.so ./lib/libcudnn.so
	ln -fs $(CWD)/cudnn/libwrapper_cudnn.so ./lib/libwrapper_cudnn.so


clean:
	cd ./cuda					&& make clean
	cd ./cudart 				&& make clean
	cd ./cublas 				&& make clean
	cd ./cublasLt 				&& make clean
	cd ./cufft 					&& make clean
	cd ./cupti 					&& make clean
	cd ./curand 				&& make clean
	cd ./cusolver 				&& make clean
	cd ./cusparse 				&& make clean
	cd ./cudnn				 	&& make clean
	cd ./dlopen_interposer		&& make clean

	
	rm -rf ./lib


