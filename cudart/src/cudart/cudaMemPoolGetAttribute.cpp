
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPoolGetAttribute)(cudaMemPool_t, enum cudaMemPoolAttr, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPoolGetAttribute(cudaMemPool_t memPool, enum cudaMemPoolAttr attr, void *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPoolGetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPoolGetAttribute = (cudaError_t (*)(cudaMemPool_t, enum cudaMemPoolAttr, void *)) dlsym(libcudart_handle, "cudaMemPoolGetAttribute");
			fprintf(stderr, "cudaMemPoolGetAttribute:%p\n", wrapper_cudaMemPoolGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPoolGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPoolGetAttribute(memPool, attr, value);
		return retval;
	}
}

