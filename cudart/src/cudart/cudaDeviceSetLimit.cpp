
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceSetLimit)(enum cudaLimit, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceSetLimit(enum cudaLimit limit, size_t value) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceSetLimit)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceSetLimit = (cudaError_t (*)(enum cudaLimit, size_t)) dlsym(libcudart_handle, "cudaDeviceSetLimit");
			fprintf(stderr, "cudaDeviceSetLimit:%p\n", wrapper_cudaDeviceSetLimit);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceSetLimit():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceSetLimit(limit, value);
		return retval;
	}
}

