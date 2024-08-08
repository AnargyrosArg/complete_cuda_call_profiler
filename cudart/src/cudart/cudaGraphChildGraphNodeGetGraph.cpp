
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphChildGraphNodeGetGraph)(cudaGraphNode_t, cudaGraph_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphChildGraphNodeGetGraph(cudaGraphNode_t node, cudaGraph_t *pGraph) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphChildGraphNodeGetGraph)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphChildGraphNodeGetGraph = (cudaError_t (*)(cudaGraphNode_t, cudaGraph_t *)) dlsym(libcudart_handle, "cudaGraphChildGraphNodeGetGraph");
			fprintf(stderr, "cudaGraphChildGraphNodeGetGraph:%p\n", wrapper_cudaGraphChildGraphNodeGetGraph);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphChildGraphNodeGetGraph():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphChildGraphNodeGetGraph(node, pGraph);
		return retval;
	}
}

