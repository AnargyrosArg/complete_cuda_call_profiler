
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolSetAccess)(cudaMemPool_t, const struct cudaMemAccessDesc *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolSetAccess(cudaMemPool_t memPool, const struct cudaMemAccessDesc *descList, size_t count) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolSetAccess)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolSetAccess = (cudaError_t (*)(cudaMemPool_t, const struct cudaMemAccessDesc *, size_t)) dlsym(libcudart_handle, "cudaMemPoolSetAccess");
			fprintf(stderr, "cudaMemPoolSetAccess:%p\n", wrapper_cudaMemPoolSetAccess);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolSetAccess():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolSetAccess(memPool, descList, count);
		return retval;
	}
}

