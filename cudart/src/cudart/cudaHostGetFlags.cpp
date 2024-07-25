
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaHostGetFlags)(unsigned int *, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaHostGetFlags(unsigned int *pFlags, void *pHost) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaHostGetFlags)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaHostGetFlags = (cudaError_t (*)(unsigned int *, void *)) dlsym(libcudart_handle, "cudaHostGetFlags");
			fprintf(stderr, "cudaHostGetFlags:%p\n", wrapper_cudaHostGetFlags);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaHostGetFlags():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaHostGetFlags(pFlags, pHost);
		return retval;
	}
}

