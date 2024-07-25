
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaThreadSetLimit)(enum cudaLimit, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaThreadSetLimit(enum cudaLimit limit, size_t value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaThreadSetLimit)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaThreadSetLimit = (cudaError_t (*)(enum cudaLimit, size_t)) dlsym(libcudart_handle, "cudaThreadSetLimit");
			fprintf(stderr, "cudaThreadSetLimit:%p\n", wrapper_cudaThreadSetLimit);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaThreadSetLimit():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaThreadSetLimit(limit, value);
		return retval;
	}
}

