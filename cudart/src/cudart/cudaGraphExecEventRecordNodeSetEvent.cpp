
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecEventRecordNodeSetEvent)(cudaGraphExec_t, cudaGraphNode_t, cudaEvent_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecEventRecordNodeSetEvent(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, cudaEvent_t event) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecEventRecordNodeSetEvent)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecEventRecordNodeSetEvent = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, cudaEvent_t)) dlsym(libcudart_handle, "cudaGraphExecEventRecordNodeSetEvent");
			fprintf(stderr, "cudaGraphExecEventRecordNodeSetEvent:%p\n", wrapper_cudaGraphExecEventRecordNodeSetEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecEventRecordNodeSetEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecEventRecordNodeSetEvent(hGraphExec, hNode, event);
		return retval;
	}
}
