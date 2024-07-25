
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsResourceSetMapFlags)(cudaGraphicsResource_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t resource, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsResourceSetMapFlags)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsResourceSetMapFlags = (cudaError_t (*)(cudaGraphicsResource_t, unsigned int)) dlsym(libcudart_handle, "cudaGraphicsResourceSetMapFlags");
			fprintf(stderr, "cudaGraphicsResourceSetMapFlags:%p\n", wrapper_cudaGraphicsResourceSetMapFlags);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsResourceSetMapFlags():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsResourceSetMapFlags(resource, flags);
		return retval;
	}
}

