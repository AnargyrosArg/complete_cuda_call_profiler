
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaThreadGetCacheConfig)(enum cudaFuncCache *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaThreadGetCacheConfig(enum cudaFuncCache *pCacheConfig) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaThreadGetCacheConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaThreadGetCacheConfig = (cudaError_t (*)(enum cudaFuncCache *)) dlsym(libcudart_handle, "cudaThreadGetCacheConfig");
			fprintf(stderr, "cudaThreadGetCacheConfig:%p\n", wrapper_cudaThreadGetCacheConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaThreadGetCacheConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaThreadGetCacheConfig(pCacheConfig);
		return retval;
	}
}

