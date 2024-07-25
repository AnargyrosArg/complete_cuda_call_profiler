
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddDependencies)(cudaGraph_t, const cudaGraphNode_t *, const cudaGraphNode_t *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddDependencies(cudaGraph_t graph, const cudaGraphNode_t *from, const cudaGraphNode_t *to, size_t numDependencies) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddDependencies)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddDependencies = (cudaError_t (*)(cudaGraph_t, const cudaGraphNode_t *, const cudaGraphNode_t *, size_t)) dlsym(libcudart_handle, "cudaGraphAddDependencies");
			fprintf(stderr, "cudaGraphAddDependencies:%p\n", wrapper_cudaGraphAddDependencies);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddDependencies():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddDependencies(graph, from, to, numDependencies);
		return retval;
	}
}

