
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsUnregisterResource)(cudaGraphicsResource_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsUnregisterResource(cudaGraphicsResource_t resource) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsUnregisterResource)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsUnregisterResource = (cudaError_t (*)(cudaGraphicsResource_t)) dlsym(libcudart_handle, "cudaGraphicsUnregisterResource");
			fprintf(stderr, "cudaGraphicsUnregisterResource:%p\n", wrapper_cudaGraphicsUnregisterResource);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsUnregisterResource():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsUnregisterResource(resource);
		return retval;
	}
}

