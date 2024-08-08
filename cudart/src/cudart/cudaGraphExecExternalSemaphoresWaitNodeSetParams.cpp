
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecExternalSemaphoresWaitNodeSetParams)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaExternalSemaphoreWaitNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecExternalSemaphoresWaitNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, const struct cudaExternalSemaphoreWaitNodeParams *nodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecExternalSemaphoresWaitNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecExternalSemaphoresWaitNodeSetParams = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaExternalSemaphoreWaitNodeParams *)) dlsym(libcudart_handle, "cudaGraphExecExternalSemaphoresWaitNodeSetParams");
			fprintf(stderr, "cudaGraphExecExternalSemaphoresWaitNodeSetParams:%p\n", wrapper_cudaGraphExecExternalSemaphoresWaitNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecExternalSemaphoresWaitNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecExternalSemaphoresWaitNodeSetParams(hGraphExec, hNode, nodeParams);
		return retval;
	}
}

