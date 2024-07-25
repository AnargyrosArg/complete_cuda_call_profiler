
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocManaged)(void **, size_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocManaged(void **devPtr, size_t size, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocManaged)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocManaged = (cudaError_t (*)(void **, size_t, unsigned int)) dlsym(libcudart_handle, "cudaMallocManaged");
			fprintf(stderr, "cudaMallocManaged:%p\n", wrapper_cudaMallocManaged);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocManaged():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocManaged(devPtr, size, flags);
		return retval;
	}
}

