
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphKernelNodeGetParams)(cudaGraphNode_t, struct cudaKernelNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphKernelNodeGetParams(cudaGraphNode_t node, struct cudaKernelNodeParams *pNodeParams) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphKernelNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphKernelNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaKernelNodeParams *)) dlsym(libcudart_handle, "cudaGraphKernelNodeGetParams");
			fprintf(stderr, "cudaGraphKernelNodeGetParams:%p\n", wrapper_cudaGraphKernelNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphKernelNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphKernelNodeGetParams(node, pNodeParams);
		return retval;
	}
}

