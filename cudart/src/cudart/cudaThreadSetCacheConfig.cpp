
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaThreadSetCacheConfig)(enum cudaFuncCache);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaThreadSetCacheConfig(enum cudaFuncCache cacheConfig) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaThreadSetCacheConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaThreadSetCacheConfig = (cudaError_t (*)(enum cudaFuncCache)) dlsym(libcudart_handle, "cudaThreadSetCacheConfig");
			fprintf(stderr, "cudaThreadSetCacheConfig:%p\n", wrapper_cudaThreadSetCacheConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaThreadSetCacheConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaThreadSetCacheConfig(cacheConfig);
		return retval;
	}
}

