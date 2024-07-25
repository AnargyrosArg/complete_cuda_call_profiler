
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsResourceGetMappedPointer)(void **, size_t *, cudaGraphicsResource_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsResourceGetMappedPointer(void **devPtr, size_t *size, cudaGraphicsResource_t resource) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsResourceGetMappedPointer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsResourceGetMappedPointer = (cudaError_t (*)(void **, size_t *, cudaGraphicsResource_t)) dlsym(libcudart_handle, "cudaGraphicsResourceGetMappedPointer");
			fprintf(stderr, "cudaGraphicsResourceGetMappedPointer:%p\n", wrapper_cudaGraphicsResourceGetMappedPointer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsResourceGetMappedPointer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsResourceGetMappedPointer(devPtr, size, resource);
		return retval;
	}
}

