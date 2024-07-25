
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddChildGraphNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, cudaGraph_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddChildGraphNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, cudaGraph_t childGraph) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddChildGraphNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddChildGraphNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, cudaGraph_t)) dlsym(libcudart_handle, "cudaGraphAddChildGraphNode");
			fprintf(stderr, "cudaGraphAddChildGraphNode:%p\n", wrapper_cudaGraphAddChildGraphNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddChildGraphNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddChildGraphNode(pGraphNode, graph, pDependencies, numDependencies, childGraph);
		return retval;
	}
}

