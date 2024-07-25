
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphHostNodeSetParams)(cudaGraphNode_t, const struct cudaHostNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphHostNodeSetParams(cudaGraphNode_t node, const struct cudaHostNodeParams *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphHostNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphHostNodeSetParams = (cudaError_t (*)(cudaGraphNode_t, const struct cudaHostNodeParams *)) dlsym(libcudart_handle, "cudaGraphHostNodeSetParams");
			fprintf(stderr, "cudaGraphHostNodeSetParams:%p\n", wrapper_cudaGraphHostNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphHostNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphHostNodeSetParams(node, pNodeParams);
		return retval;
	}
}

