
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamCopyAttributes)(cudaStream_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamCopyAttributes(cudaStream_t dst, cudaStream_t src) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamCopyAttributes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamCopyAttributes = (cudaError_t (*)(cudaStream_t, cudaStream_t)) dlsym(libcudart_handle, "cudaStreamCopyAttributes");
			fprintf(stderr, "cudaStreamCopyAttributes:%p\n", wrapper_cudaStreamCopyAttributes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamCopyAttributes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamCopyAttributes(dst, src);
		return retval;
	}
}

