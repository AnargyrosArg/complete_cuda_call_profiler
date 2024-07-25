
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecMemcpyNodeSetParams)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaMemcpy3DParms *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecMemcpyNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const struct cudaMemcpy3DParms *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecMemcpyNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecMemcpyNodeSetParams = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaMemcpy3DParms *)) dlsym(libcudart_handle, "cudaGraphExecMemcpyNodeSetParams");
			fprintf(stderr, "cudaGraphExecMemcpyNodeSetParams:%p\n", wrapper_cudaGraphExecMemcpyNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecMemcpyNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecMemcpyNodeSetParams(hGraphExec, node, pNodeParams);
		return retval;
	}
}

