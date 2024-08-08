
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphAddEventRecordNode)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, cudaEvent_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphAddEventRecordNode(cudaGraphNode_t *pGraphNode, cudaGraph_t graph, const cudaGraphNode_t *pDependencies, size_t numDependencies, cudaEvent_t event) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphAddEventRecordNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphAddEventRecordNode = (cudaError_t (*)(cudaGraphNode_t *, cudaGraph_t, const cudaGraphNode_t *, size_t, cudaEvent_t)) dlsym(libcudart_handle, "cudaGraphAddEventRecordNode");
			fprintf(stderr, "cudaGraphAddEventRecordNode:%p\n", wrapper_cudaGraphAddEventRecordNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphAddEventRecordNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphAddEventRecordNode(pGraphNode, graph, pDependencies, numDependencies, event);
		return retval;
	}
}

