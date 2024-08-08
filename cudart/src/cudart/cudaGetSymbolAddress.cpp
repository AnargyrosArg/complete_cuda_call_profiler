
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetSymbolAddress)(void **, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetSymbolAddress(void **devPtr, const void *symbol) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetSymbolAddress)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetSymbolAddress = (cudaError_t (*)(void **, const void *)) dlsym(libcudart_handle, "cudaGetSymbolAddress");
			fprintf(stderr, "cudaGetSymbolAddress:%p\n", wrapper_cudaGetSymbolAddress);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetSymbolAddress():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetSymbolAddress(devPtr, symbol);
		return retval;
	}
}

