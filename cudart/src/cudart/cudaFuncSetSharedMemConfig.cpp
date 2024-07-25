
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFuncSetSharedMemConfig)(const void *, enum cudaSharedMemConfig);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFuncSetSharedMemConfig(const void *func, enum cudaSharedMemConfig config) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFuncSetSharedMemConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFuncSetSharedMemConfig = (cudaError_t (*)(const void *, enum cudaSharedMemConfig)) dlsym(libcudart_handle, "cudaFuncSetSharedMemConfig");
			fprintf(stderr, "cudaFuncSetSharedMemConfig:%p\n", wrapper_cudaFuncSetSharedMemConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFuncSetSharedMemConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFuncSetSharedMemConfig(func, config);
		return retval;
	}
}

