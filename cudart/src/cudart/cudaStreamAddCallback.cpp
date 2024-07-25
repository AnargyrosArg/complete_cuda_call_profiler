
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamAddCallback)(cudaStream_t, cudaStreamCallback_t, void *, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamAddCallback(cudaStream_t stream, cudaStreamCallback_t callback, void *userData, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamAddCallback)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamAddCallback = (cudaError_t (*)(cudaStream_t, cudaStreamCallback_t, void *, unsigned int)) dlsym(libcudart_handle, "cudaStreamAddCallback");
			fprintf(stderr, "cudaStreamAddCallback:%p\n", wrapper_cudaStreamAddCallback);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamAddCallback():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamAddCallback(stream, callback, userData, flags);
		return retval;
	}
}

