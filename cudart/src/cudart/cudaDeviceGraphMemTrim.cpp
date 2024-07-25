
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGraphMemTrim)(int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGraphMemTrim(int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGraphMemTrim)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGraphMemTrim = (cudaError_t (*)(int)) dlsym(libcudart_handle, "cudaDeviceGraphMemTrim");
			fprintf(stderr, "cudaDeviceGraphMemTrim:%p\n", wrapper_cudaDeviceGraphMemTrim);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGraphMemTrim():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGraphMemTrim(device);
		return retval;
	}
}

