
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExternalSemaphoresWaitNodeGetParams)(cudaGraphNode_t, struct cudaExternalSemaphoreWaitNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExternalSemaphoresWaitNodeGetParams(cudaGraphNode_t hNode, struct cudaExternalSemaphoreWaitNodeParams *params_out) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExternalSemaphoresWaitNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExternalSemaphoresWaitNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaExternalSemaphoreWaitNodeParams *)) dlsym(libcudart_handle, "cudaGraphExternalSemaphoresWaitNodeGetParams");
			fprintf(stderr, "cudaGraphExternalSemaphoresWaitNodeGetParams:%p\n", wrapper_cudaGraphExternalSemaphoresWaitNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExternalSemaphoresWaitNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExternalSemaphoresWaitNodeGetParams(hNode, params_out);
		return retval;
	}
}

