
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFreeHost)(void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFreeHost(void *ptr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFreeHost)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFreeHost = (cudaError_t (*)(void *)) dlsym(libcudart_handle, "cudaFreeHost");
			fprintf(stderr, "cudaFreeHost:%p\n", wrapper_cudaFreeHost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFreeHost():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFreeHost(ptr);
		return retval;
	}
}

