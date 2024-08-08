
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExternalSemaphoresSignalNodeSetParams)(cudaGraphNode_t, const struct cudaExternalSemaphoreSignalNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExternalSemaphoresSignalNodeSetParams(cudaGraphNode_t hNode, const struct cudaExternalSemaphoreSignalNodeParams *nodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExternalSemaphoresSignalNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExternalSemaphoresSignalNodeSetParams = (cudaError_t (*)(cudaGraphNode_t, const struct cudaExternalSemaphoreSignalNodeParams *)) dlsym(libcudart_handle, "cudaGraphExternalSemaphoresSignalNodeSetParams");
			fprintf(stderr, "cudaGraphExternalSemaphoresSignalNodeSetParams:%p\n", wrapper_cudaGraphExternalSemaphoresSignalNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExternalSemaphoresSignalNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExternalSemaphoresSignalNodeSetParams(hNode, nodeParams);
		return retval;
	}
}

