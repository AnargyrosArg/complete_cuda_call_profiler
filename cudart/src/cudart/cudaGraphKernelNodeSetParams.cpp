
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphKernelNodeSetParams)(cudaGraphNode_t, const struct cudaKernelNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphKernelNodeSetParams(cudaGraphNode_t node, const struct cudaKernelNodeParams *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphKernelNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphKernelNodeSetParams = (cudaError_t (*)(cudaGraphNode_t, const struct cudaKernelNodeParams *)) dlsym(libcudart_handle, "cudaGraphKernelNodeSetParams");
			fprintf(stderr, "cudaGraphKernelNodeSetParams:%p\n", wrapper_cudaGraphKernelNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphKernelNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphKernelNodeSetParams(node, pNodeParams);
		return retval;
	}
}

