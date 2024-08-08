
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExternalSemaphoresSignalNodeGetParams)(cudaGraphNode_t, struct cudaExternalSemaphoreSignalNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExternalSemaphoresSignalNodeGetParams(cudaGraphNode_t hNode, struct cudaExternalSemaphoreSignalNodeParams *params_out) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExternalSemaphoresSignalNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExternalSemaphoresSignalNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaExternalSemaphoreSignalNodeParams *)) dlsym(libcudart_handle, "cudaGraphExternalSemaphoresSignalNodeGetParams");
			fprintf(stderr, "cudaGraphExternalSemaphoresSignalNodeGetParams:%p\n", wrapper_cudaGraphExternalSemaphoresSignalNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExternalSemaphoresSignalNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExternalSemaphoresSignalNodeGetParams(hNode, params_out);
		return retval;
	}
}

