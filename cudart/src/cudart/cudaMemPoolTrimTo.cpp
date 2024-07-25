
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolTrimTo)(cudaMemPool_t, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolTrimTo(cudaMemPool_t memPool, size_t minBytesToKeep) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolTrimTo)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolTrimTo = (cudaError_t (*)(cudaMemPool_t, size_t)) dlsym(libcudart_handle, "cudaMemPoolTrimTo");
			fprintf(stderr, "cudaMemPoolTrimTo:%p\n", wrapper_cudaMemPoolTrimTo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolTrimTo():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolTrimTo(memPool, minBytesToKeep);
		return retval;
	}
}
