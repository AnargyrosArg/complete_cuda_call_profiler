
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphicsMapResources)(int, cudaGraphicsResource_t *, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphicsMapResources(int count, cudaGraphicsResource_t *resources, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphicsMapResources)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphicsMapResources = (cudaError_t (*)(int, cudaGraphicsResource_t *, cudaStream_t)) dlsym(libcudart_handle, "cudaGraphicsMapResources");
			fprintf(stderr, "cudaGraphicsMapResources:%p\n", wrapper_cudaGraphicsMapResources);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphicsMapResources():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphicsMapResources(count, resources, stream);
		return retval;
	}
}

