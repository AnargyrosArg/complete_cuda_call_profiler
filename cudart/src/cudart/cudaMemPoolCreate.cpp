
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolCreate)(cudaMemPool_t *, const struct cudaMemPoolProps *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolCreate(cudaMemPool_t *memPool, const struct cudaMemPoolProps *poolProps) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolCreate)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolCreate = (cudaError_t (*)(cudaMemPool_t *, const struct cudaMemPoolProps *)) dlsym(libcudart_handle, "cudaMemPoolCreate");
			fprintf(stderr, "cudaMemPoolCreate:%p\n", wrapper_cudaMemPoolCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolCreate(memPool, poolProps);
		return retval;
	}
}

