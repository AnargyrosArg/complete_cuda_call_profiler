
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddMemcpyNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaMemcpy3DParms *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddMemcpyNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, const struct cudaMemcpy3DParms *pCopyParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddMemcpyNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddMemcpyNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, const struct cudaMemcpy3DParms *)) dlsym(libcudart_handle, "cudaGraphAddMemcpyNode");
			fprintf(stderr, "cudaGraphAddMemcpyNode:%p\n", wrapper_cudaGraphAddMemcpyNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddMemcpyNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddMemcpyNode(pGraphNode, graph, pDependencies, numDependencies, pCopyParams);
		return retval;
	}
}
