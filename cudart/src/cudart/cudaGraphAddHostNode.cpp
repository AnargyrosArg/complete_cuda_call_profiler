
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddHostNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaHostNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddHostNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, const struct cudaHostNodeParams *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddHostNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddHostNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaHostNodeParams *)) dlsym(libcudart_handle, "cudaGraphAddHostNode");
			fprintf(stderr, "cudaGraphAddHostNode:%p\n", wrapper_cudaGraphAddHostNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddHostNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddHostNode(pGraphNode, graph, pDependencies, numDependencies, pNodeParams);
		return retval;
	}
}

