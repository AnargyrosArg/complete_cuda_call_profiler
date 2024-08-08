
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetSymbolSize)(size_t *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetSymbolSize(size_t *size, const void *symbol) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetSymbolSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetSymbolSize = (cudaError_t (*)(size_t *, const void *)) dlsym(libcudart_handle, "cudaGetSymbolSize");
			fprintf(stderr, "cudaGetSymbolSize:%p\n", wrapper_cudaGetSymbolSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetSymbolSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetSymbolSize(size, symbol);
		return retval;
	}
}

