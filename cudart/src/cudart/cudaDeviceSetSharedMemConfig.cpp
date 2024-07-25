
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceSetSharedMemConfig)(enum cudaSharedMemConfig);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceSetSharedMemConfig(enum cudaSharedMemConfig config) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceSetSharedMemConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceSetSharedMemConfig = (cudaError_t (*)(enum cudaSharedMemConfig)) dlsym(libcudart_handle, "cudaDeviceSetSharedMemConfig");
			fprintf(stderr, "cudaDeviceSetSharedMemConfig:%p\n", wrapper_cudaDeviceSetSharedMemConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceSetSharedMemConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceSetSharedMemConfig(config);
		return retval;
	}
}

