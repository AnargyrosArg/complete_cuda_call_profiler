
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaHostGetDevicePointer)(void **, void *, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaHostGetDevicePointer(void **pDevice, void *pHost, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaHostGetDevicePointer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaHostGetDevicePointer = (cudaError_t (*)(void **, void *, unsigned int)) dlsym(libcudart_handle, "cudaHostGetDevicePointer");
			fprintf(stderr, "cudaHostGetDevicePointer:%p\n", wrapper_cudaHostGetDevicePointer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaHostGetDevicePointer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaHostGetDevicePointer(pDevice, pHost, flags);
		return retval;
	}
}

