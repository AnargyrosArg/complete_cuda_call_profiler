
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecKernelNodeSetParams)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaKernelNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecKernelNodeSetParams(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const struct cudaKernelNodeParams *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecKernelNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecKernelNodeSetParams = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, const struct cudaKernelNodeParams *)) dlsym(libcudart_handle, "cudaGraphExecKernelNodeSetParams");
			fprintf(stderr, "cudaGraphExecKernelNodeSetParams:%p\n", wrapper_cudaGraphExecKernelNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecKernelNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecKernelNodeSetParams(hGraphExec, node, pNodeParams);
		return retval;
	}
}

