
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceSetCacheConfig)(enum cudaFuncCache);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceSetCacheConfig(enum cudaFuncCache cacheConfig) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceSetCacheConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceSetCacheConfig = (cudaError_t (*)(enum cudaFuncCache)) dlsym(libcudart_handle, "cudaDeviceSetCacheConfig");
			fprintf(stderr, "cudaDeviceSetCacheConfig:%p\n", wrapper_cudaDeviceSetCacheConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceSetCacheConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceSetCacheConfig(cacheConfig);
		return retval;
	}
}

