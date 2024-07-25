
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetFuncBySymbol)(cudaFunction_t *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetFuncBySymbol(cudaFunction_t *functionPtr, const void *symbolPtr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetFuncBySymbol)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetFuncBySymbol = (cudaError_t (*)(cudaFunction_t *, const void *)) dlsym(libcudart_handle, "cudaGetFuncBySymbol");
			fprintf(stderr, "cudaGetFuncBySymbol:%p\n", wrapper_cudaGetFuncBySymbol);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetFuncBySymbol():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetFuncBySymbol(functionPtr, symbolPtr);
		return retval;
	}
}

