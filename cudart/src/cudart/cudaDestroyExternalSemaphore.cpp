
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDestroyExternalSemaphore)(cudaExternalSemaphore_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDestroyExternalSemaphore(cudaExternalSemaphore_t extSem) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDestroyExternalSemaphore)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDestroyExternalSemaphore = (cudaError_t (*)(cudaExternalSemaphore_t)) dlsym(libcudart_handle, "cudaDestroyExternalSemaphore");
			fprintf(stderr, "cudaDestroyExternalSemaphore:%p\n", wrapper_cudaDestroyExternalSemaphore);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDestroyExternalSemaphore():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDestroyExternalSemaphore(extSem);
		return retval;
	}
}

