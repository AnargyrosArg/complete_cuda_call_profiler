
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetLimit)(size_t *, enum cudaLimit);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetLimit(size_t *pValue, enum cudaLimit limit) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetLimit)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetLimit = (cudaError_t (*)(size_t *, enum cudaLimit)) dlsym(libcudart_handle, "cudaDeviceGetLimit");
			fprintf(stderr, "cudaDeviceGetLimit:%p\n", wrapper_cudaDeviceGetLimit);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetLimit():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetLimit(pValue, limit);
		return retval;
	}
}

