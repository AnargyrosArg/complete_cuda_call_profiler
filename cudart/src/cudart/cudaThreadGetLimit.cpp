
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaThreadGetLimit)(size_t *, enum cudaLimit);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaThreadGetLimit(size_t *pValue, enum cudaLimit limit) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaThreadGetLimit)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaThreadGetLimit = (cudaError_t (*)(size_t *, enum cudaLimit)) dlsym(libcudart_handle, "cudaThreadGetLimit");
			fprintf(stderr, "cudaThreadGetLimit:%p\n", wrapper_cudaThreadGetLimit);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaThreadGetLimit():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaThreadGetLimit(pValue, limit);
		return retval;
	}
}

