
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddExternalSemaphoresWaitNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaExternalSemaphoreWaitNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddExternalSemaphoresWaitNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, const struct cudaExternalSemaphoreWaitNodeParams *nodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddExternalSemaphoresWaitNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddExternalSemaphoresWaitNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaExternalSemaphoreWaitNodeParams *)) dlsym(libcudart_handle, "cudaGraphAddExternalSemaphoresWaitNode");
			fprintf(stderr, "cudaGraphAddExternalSemaphoresWaitNode:%p\n", wrapper_cudaGraphAddExternalSemaphoresWaitNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddExternalSemaphoresWaitNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddExternalSemaphoresWaitNode(pGraphNode, graph, pDependencies, numDependencies, nodeParams);
		return retval;
	}
}
