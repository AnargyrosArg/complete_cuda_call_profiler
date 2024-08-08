
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolExportToShareableHandle)(void *, cudaMemPool_t, enum cudaMemAllocationHandleType, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolExportToShareableHandle(void *shareableHandle, cudaMemPool_t memPool, enum cudaMemAllocationHandleType handleType, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolExportToShareableHandle)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolExportToShareableHandle = (cudaError_t (*)(void *, cudaMemPool_t, enum cudaMemAllocationHandleType, unsigned int)) dlsym(libcudart_handle, "cudaMemPoolExportToShareableHandle");
			fprintf(stderr, "cudaMemPoolExportToShareableHandle:%p\n", wrapper_cudaMemPoolExportToShareableHandle);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolExportToShareableHandle():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolExportToShareableHandle(shareableHandle, memPool, handleType, flags);
		return retval;
	}
}

