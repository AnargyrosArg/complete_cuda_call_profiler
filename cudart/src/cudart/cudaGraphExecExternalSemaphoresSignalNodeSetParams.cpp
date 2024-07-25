
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecExternalSemaphoresSignalNodeSetParams)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaExternalSemaphoreSignalNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecExternalSemaphoresSignalNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, const struct cudaExternalSemaphoreSignalNodeParams *nodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecExternalSemaphoresSignalNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecExternalSemaphoresSignalNodeSetParams = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaExternalSemaphoreSignalNodeParams *)) dlsym(libcudart_handle, "cudaGraphExecExternalSemaphoresSignalNodeSetParams");
			fprintf(stderr, "cudaGraphExecExternalSemaphoresSignalNodeSetParams:%p\n", wrapper_cudaGraphExecExternalSemaphoresSignalNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecExternalSemaphoresSignalNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecExternalSemaphoresSignalNodeSetParams(hGraphExec, hNode, nodeParams);
		return retval;
	}
}

