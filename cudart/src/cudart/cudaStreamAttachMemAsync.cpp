
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamAttachMemAsync)(cudaStream_t, void *, size_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamAttachMemAsync(cudaStream_t stream, void *devPtr, size_t length, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamAttachMemAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamAttachMemAsync = (cudaError_t (*)(cudaStream_t, void *, size_t, unsigned int)) dlsym(libcudart_handle, "cudaStreamAttachMemAsync");
			fprintf(stderr, "cudaStreamAttachMemAsync:%p\n", wrapper_cudaStreamAttachMemAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamAttachMemAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamAttachMemAsync(stream, devPtr, length, flags);
		return retval;
	}
}

