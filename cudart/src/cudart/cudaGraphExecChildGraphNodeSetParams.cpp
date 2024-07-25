
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecChildGraphNodeSetParams)(cudaGraphExec_t, cudaGraphNode_t, cudaGraph_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecChildGraphNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, cudaGraph_t childGraph) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecChildGraphNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecChildGraphNodeSetParams = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, cudaGraph_t)) dlsym(libcudart_handle, "cudaGraphExecChildGraphNodeSetParams");
			fprintf(stderr, "cudaGraphExecChildGraphNodeSetParams:%p\n", wrapper_cudaGraphExecChildGraphNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecChildGraphNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecChildGraphNodeSetParams(hGraphExec, node, childGraph);
		return retval;
	}
}

