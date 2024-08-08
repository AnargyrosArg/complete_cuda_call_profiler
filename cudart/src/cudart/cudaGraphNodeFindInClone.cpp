
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphNodeFindInClone)(cudaGraphNode_t *, cudaGraphNode_t, cudaGraph_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphNodeFindInClone(cudaGraphNode_t *pNode, cudaGraphNode_t originalNode, cudaGraph_t clonedGraph) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphNodeFindInClone)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphNodeFindInClone = (cudaError_t (*)(cudaGraphNode_t *, cudaGraphNode_t, cudaGraph_t)) dlsym(libcudart_handle, "cudaGraphNodeFindInClone");
			fprintf(stderr, "cudaGraphNodeFindInClone:%p\n", wrapper_cudaGraphNodeFindInClone);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphNodeFindInClone():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphNodeFindInClone(pNode, originalNode, clonedGraph);
		return retval;
	}
}

