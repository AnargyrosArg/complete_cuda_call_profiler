
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocHost)(void **, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocHost(void **ptr, size_t size) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocHost)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocHost = (cudaError_t (*)(void **, size_t)) dlsym(libcudart_handle, "cudaMallocHost");
			fprintf(stderr, "cudaMallocHost:%p\n", wrapper_cudaMallocHost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocHost():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocHost(ptr, size);
		return retval;
	}
}

