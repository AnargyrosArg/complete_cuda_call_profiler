
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFuncSetCacheConfig)(const void *, enum cudaFuncCache);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFuncSetCacheConfig(const void *func, enum cudaFuncCache cacheConfig) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFuncSetCacheConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFuncSetCacheConfig = (cudaError_t (*)(const void *, enum cudaFuncCache)) dlsym(libcudart_handle, "cudaFuncSetCacheConfig");
			fprintf(stderr, "cudaFuncSetCacheConfig:%p\n", wrapper_cudaFuncSetCacheConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFuncSetCacheConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFuncSetCacheConfig(func, cacheConfig);
		return retval;
	}
}
