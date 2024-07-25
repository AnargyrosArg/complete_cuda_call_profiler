
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolGetAccess)(enum cudaMemAccessFlags *, cudaMemPool_t, struct cudaMemLocation *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolGetAccess(enum cudaMemAccessFlags *flags, cudaMemPool_t memPool, struct cudaMemLocation *location) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolGetAccess)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolGetAccess = (cudaError_t (*)(enum cudaMemAccessFlags *, cudaMemPool_t, struct cudaMemLocation *)) dlsym(libcudart_handle, "cudaMemPoolGetAccess");
			fprintf(stderr, "cudaMemPoolGetAccess:%p\n", wrapper_cudaMemPoolGetAccess);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolGetAccess():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolGetAccess(flags, memPool, location);
		return retval;
	}
}

