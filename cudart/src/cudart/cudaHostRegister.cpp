
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaHostRegister)(void *, size_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaHostRegister(void *ptr, size_t size, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaHostRegister)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaHostRegister = (cudaError_t (*)(void *, size_t, unsigned int)) dlsym(libcudart_handle, "cudaHostRegister");
			fprintf(stderr, "cudaHostRegister:%p\n", wrapper_cudaHostRegister);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaHostRegister():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaHostRegister(ptr, size, flags);
		return retval;
	}
}

