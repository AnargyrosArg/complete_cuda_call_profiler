
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExternalSemaphoresWaitNodeSetParams)(cudaGraphNode_t, const struct cudaExternalSemaphoreWaitNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExternalSemaphoresWaitNodeSetParams(cudaGraphNode_t hNode, const struct cudaExternalSemaphoreWaitNodeParams *nodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExternalSemaphoresWaitNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExternalSemaphoresWaitNodeSetParams = (cudaError_t (*)(cudaGraphNode_t, const struct cudaExternalSemaphoreWaitNodeParams *)) dlsym(libcudart_handle, "cudaGraphExternalSemaphoresWaitNodeSetParams");
			fprintf(stderr, "cudaGraphExternalSemaphoresWaitNodeSetParams:%p\n", wrapper_cudaGraphExternalSemaphoresWaitNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExternalSemaphoresWaitNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExternalSemaphoresWaitNodeSetParams(hNode, nodeParams);
		return retval;
	}
}

