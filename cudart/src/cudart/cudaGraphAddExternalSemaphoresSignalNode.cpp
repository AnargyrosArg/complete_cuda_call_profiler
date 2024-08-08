
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddExternalSemaphoresSignalNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaExternalSemaphoreSignalNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddExternalSemaphoresSignalNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, const struct cudaExternalSemaphoreSignalNodeParams *nodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddExternalSemaphoresSignalNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddExternalSemaphoresSignalNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaExternalSemaphoreSignalNodeParams *)) dlsym(libcudart_handle, "cudaGraphAddExternalSemaphoresSignalNode");
			fprintf(stderr, "cudaGraphAddExternalSemaphoresSignalNode:%p\n", wrapper_cudaGraphAddExternalSemaphoresSignalNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddExternalSemaphoresSignalNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddExternalSemaphoresSignalNode(pGraphNode, graph, pDependencies, numDependencies, nodeParams);
		return retval;
	}
}

