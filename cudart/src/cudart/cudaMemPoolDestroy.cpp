
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolDestroy)(cudaMemPool_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolDestroy(cudaMemPool_t memPool) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolDestroy)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolDestroy = (cudaError_t (*)(cudaMemPool_t)) dlsym(libcudart_handle, "cudaMemPoolDestroy");
			fprintf(stderr, "cudaMemPoolDestroy:%p\n", wrapper_cudaMemPoolDestroy);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolDestroy():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolDestroy(memPool);
		return retval;
	}
}

