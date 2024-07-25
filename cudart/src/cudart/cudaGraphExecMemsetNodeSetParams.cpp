
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecMemsetNodeSetParams)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaMemsetParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecMemsetNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const struct cudaMemsetParams *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecMemsetNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecMemsetNodeSetParams = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaMemsetParams *)) dlsym(libcudart_handle, "cudaGraphExecMemsetNodeSetParams");
			fprintf(stderr, "cudaGraphExecMemsetNodeSetParams:%p\n", wrapper_cudaGraphExecMemsetNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecMemsetNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecMemsetNodeSetParams(hGraphExec, node, pNodeParams);
		return retval;
	}
}

