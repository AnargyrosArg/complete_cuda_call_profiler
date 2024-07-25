
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphEventWaitNodeSetEvent)(cudaGraphNode_t, cudaEvent_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphEventWaitNodeSetEvent(cudaGraphNode_t node, cudaEvent_t event) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphEventWaitNodeSetEvent)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphEventWaitNodeSetEvent = (cudaError_t (*)(cudaGraphNode_t, cudaEvent_t)) dlsym(libcudart_handle, "cudaGraphEventWaitNodeSetEvent");
			fprintf(stderr, "cudaGraphEventWaitNodeSetEvent:%p\n", wrapper_cudaGraphEventWaitNodeSetEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphEventWaitNodeSetEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphEventWaitNodeSetEvent(node, event);
		return retval;
	}
}

