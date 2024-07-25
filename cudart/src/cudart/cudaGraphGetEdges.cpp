
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphGetEdges)(cudaGraph_t, cudaGraphNode_t *, cudaGraphNode_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphGetEdges(cudaGraph_t graph, cudaGraphNode_t *from, cudaGraphNode_t *to, size_t *numEdges) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphGetEdges)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphGetEdges = (cudaError_t (*)(cudaGraph_t, cudaGraphNode_t *, cudaGraphNode_t *, size_t *)) dlsym(libcudart_handle, "cudaGraphGetEdges");
			fprintf(stderr, "cudaGraphGetEdges:%p\n", wrapper_cudaGraphGetEdges);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphGetEdges():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphGetEdges(graph, from, to, numEdges);
		return retval;
	}
}

