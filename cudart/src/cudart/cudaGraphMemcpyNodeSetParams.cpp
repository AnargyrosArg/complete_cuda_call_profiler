
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemcpyNodeSetParams)(cudaGraphNode_t, const struct cudaMemcpy3DParms *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemcpyNodeSetParams(cudaGraphNode_t node, const struct cudaMemcpy3DParms *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemcpyNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemcpyNodeSetParams = (cudaError_t (*)(cudaGraphNode_t, const struct cudaMemcpy3DParms *)) dlsym(libcudart_handle, "cudaGraphMemcpyNodeSetParams");
			fprintf(stderr, "cudaGraphMemcpyNodeSetParams:%p\n", wrapper_cudaGraphMemcpyNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemcpyNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemcpyNodeSetParams(node, pNodeParams);
		return retval;
	}
}

