
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolImportFromShareableHandle)(cudaMemPool_t *, void *, enum cudaMemAllocationHandleType, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolImportFromShareableHandle(cudaMemPool_t *memPool, void *shareableHandle, enum cudaMemAllocationHandleType handleType, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolImportFromShareableHandle)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolImportFromShareableHandle = (cudaError_t (*)(cudaMemPool_t *, void *, enum cudaMemAllocationHandleType, unsigned int)) dlsym(libcudart_handle, "cudaMemPoolImportFromShareableHandle");
			fprintf(stderr, "cudaMemPoolImportFromShareableHandle:%p\n", wrapper_cudaMemPoolImportFromShareableHandle);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolImportFromShareableHandle():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolImportFromShareableHandle(memPool, shareableHandle, handleType, flags);
		return retval;
	}
}

