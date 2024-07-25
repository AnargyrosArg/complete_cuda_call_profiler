
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamUpdateCaptureDependencies)(cudaStream_t, cudaGraphNode_t *, size_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamUpdateCaptureDependencies(cudaStream_t stream, cudaGraphNode_t *dependencies, size_t numDependencies, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamUpdateCaptureDependencies)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamUpdateCaptureDependencies = (cudaError_t (*)(cudaStream_t, cudaGraphNode_t *, size_t, unsigned int)) dlsym(libcudart_handle, "cudaStreamUpdateCaptureDependencies");
			fprintf(stderr, "cudaStreamUpdateCaptureDependencies:%p\n", wrapper_cudaStreamUpdateCaptureDependencies);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamUpdateCaptureDependencies():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamUpdateCaptureDependencies(stream, dependencies, numDependencies, flags);
		return retval;
	}
}

