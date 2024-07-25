
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
const char * (*wrapper_cudaGetErrorString)(cudaError_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	const char * cudaGetErrorString(cudaError_t error) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetErrorString)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetErrorString = (const char * (*)(cudaError_t)) dlsym(libcudart_handle, "cudaGetErrorString");
			fprintf(stderr, "cudaGetErrorString:%p\n", wrapper_cudaGetErrorString);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetErrorString():%s\n", __dlerror);
			fflush(stderr);
		}
		const char * retval = wrapper_cudaGetErrorString(error);
		return retval;
	}
}

