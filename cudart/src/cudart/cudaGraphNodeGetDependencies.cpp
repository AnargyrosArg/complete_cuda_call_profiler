
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphNodeGetDependencies)(cudaGraphNode_t, cudaGraphNode_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphNodeGetDependencies(cudaGraphNode_t node, cudaGraphNode_t *pDependencies, size_t *pNumDependencies) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphNodeGetDependencies)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphNodeGetDependencies = (cudaError_t (*)(cudaGraphNode_t, cudaGraphNode_t *, size_t *)) dlsym(libcudart_handle, "cudaGraphNodeGetDependencies");
			fprintf(stderr, "cudaGraphNodeGetDependencies:%p\n", wrapper_cudaGraphNodeGetDependencies);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphNodeGetDependencies():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphNodeGetDependencies(node, pDependencies, pNumDependencies);
		return retval;
	}
}

