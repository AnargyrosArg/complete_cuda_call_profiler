
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphGetRootNodes)(cudaGraph_t, cudaGraphNode_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphGetRootNodes(cudaGraph_t graph, cudaGraphNode_t *pRootNodes, size_t *pNumRootNodes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphGetRootNodes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphGetRootNodes = (cudaError_t (*)(cudaGraph_t, cudaGraphNode_t *, size_t *)) dlsym(libcudart_handle, "cudaGraphGetRootNodes");
			fprintf(stderr, "cudaGraphGetRootNodes:%p\n", wrapper_cudaGraphGetRootNodes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphGetRootNodes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphGetRootNodes(graph, pRootNodes, pNumRootNodes);
		return retval;
	}
}

