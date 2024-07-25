
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphGetNodes)(cudaGraph_t, cudaGraphNode_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphGetNodes(cudaGraph_t graph, cudaGraphNode_t *nodes, size_t *numNodes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphGetNodes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphGetNodes = (cudaError_t (*)(cudaGraph_t, cudaGraphNode_t *, size_t *)) dlsym(libcudart_handle, "cudaGraphGetNodes");
			fprintf(stderr, "cudaGraphGetNodes:%p\n", wrapper_cudaGraphGetNodes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphGetNodes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphGetNodes(graph, nodes, numNodes);
		return retval;
	}
}

