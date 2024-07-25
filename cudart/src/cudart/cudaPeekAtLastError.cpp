
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaPeekAtLastError)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaPeekAtLastError() {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaPeekAtLastError)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaPeekAtLastError = (cudaError_t (*)()) dlsym(libcudart_handle, "cudaPeekAtLastError");
			fprintf(stderr, "cudaPeekAtLastError:%p\n", wrapper_cudaPeekAtLastError);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaPeekAtLastError():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaPeekAtLastError();
		return retval;
	}
}
