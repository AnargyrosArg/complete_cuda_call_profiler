
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphEventWaitNodeGetEvent)(cudaGraphNode_t, cudaEvent_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphEventWaitNodeGetEvent(cudaGraphNode_t node, cudaEvent_t *event_out) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphEventWaitNodeGetEvent)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphEventWaitNodeGetEvent = (cudaError_t (*)(cudaGraphNode_t, cudaEvent_t *)) dlsym(libcudart_handle, "cudaGraphEventWaitNodeGetEvent");
			fprintf(stderr, "cudaGraphEventWaitNodeGetEvent:%p\n", wrapper_cudaGraphEventWaitNodeGetEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphEventWaitNodeGetEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphEventWaitNodeGetEvent(node, event_out);
		return retval;
	}
}

