
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecUpdate)(cudaGraphExec_t, cudaGraph_t, cudaGraphNode_t *, enum cudaGraphExecUpdateResult *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecUpdate(cudaGraphExec_t hGraphExec, cudaGraph_t hGraph, cudaGraphNode_t *hErrorNode_out, enum cudaGraphExecUpdateResult *updateResult_out) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecUpdate)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecUpdate = (cudaError_t (*)(cudaGraphExec_t, cudaGraph_t, cudaGraphNode_t *, enum cudaGraphExecUpdateResult *)) dlsym(libcudart_handle, "cudaGraphExecUpdate");
			fprintf(stderr, "cudaGraphExecUpdate:%p\n", wrapper_cudaGraphExecUpdate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecUpdate():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecUpdate(hGraphExec, hGraph, hErrorNode_out, updateResult_out);
		return retval;
	}
}

