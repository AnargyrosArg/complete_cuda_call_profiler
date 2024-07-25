
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDestroyExternalMemory)(cudaExternalMemory_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDestroyExternalMemory(cudaExternalMemory_t extMem) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDestroyExternalMemory)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDestroyExternalMemory = (cudaError_t (*)(cudaExternalMemory_t)) dlsym(libcudart_handle, "cudaDestroyExternalMemory");
			fprintf(stderr, "cudaDestroyExternalMemory:%p\n", wrapper_cudaDestroyExternalMemory);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDestroyExternalMemory():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDestroyExternalMemory(extMem);
		return retval;
	}
}

