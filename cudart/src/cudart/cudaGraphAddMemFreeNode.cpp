
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddMemFreeNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddMemFreeNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, void *dptr) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddMemFreeNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddMemFreeNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, void *)) dlsym(libcudart_handle, "cudaGraphAddMemFreeNode");
			fprintf(stderr, "cudaGraphAddMemFreeNode:%p\n", wrapper_cudaGraphAddMemFreeNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddMemFreeNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddMemFreeNode(pGraphNode, graph, pDependencies, numDependencies, dptr);
		return retval;
	}
}

