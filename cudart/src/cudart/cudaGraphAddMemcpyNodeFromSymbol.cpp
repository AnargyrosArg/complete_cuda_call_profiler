
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddMemcpyNodeFromSymbol)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, void *, const void *, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddMemcpyNodeFromSymbol(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, void *dst, const void *symbol, size_t count, size_t offset, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddMemcpyNodeFromSymbol)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddMemcpyNodeFromSymbol = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, void *, const void *, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaGraphAddMemcpyNodeFromSymbol");
			fprintf(stderr, "cudaGraphAddMemcpyNodeFromSymbol:%p\n", wrapper_cudaGraphAddMemcpyNodeFromSymbol);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddMemcpyNodeFromSymbol():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddMemcpyNodeFromSymbol(pGraphNode, graph, pDependencies, numDependencies, dst, symbol, count, offset, kind);
		return retval;
	}
}

