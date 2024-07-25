
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetDriverEntryPoint)(const char *, void **, unsigned long long);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetDriverEntryPoint(const char *symbol, void **funcPtr, unsigned long long flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetDriverEntryPoint)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetDriverEntryPoint = (cudaError_t (*)(const char *, void **, unsigned long long)) dlsym(libcudart_handle, "cudaGetDriverEntryPoint");
			fprintf(stderr, "cudaGetDriverEntryPoint:%p\n", wrapper_cudaGetDriverEntryPoint);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetDriverEntryPoint():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetDriverEntryPoint(symbol, funcPtr, flags);
		return retval;
	}
}

