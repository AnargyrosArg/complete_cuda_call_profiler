
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphKernelNodeCopyAttributes)(cudaGraphNode_t, cudaGraphNode_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphKernelNodeCopyAttributes(cudaGraphNode_t hSrc, cudaGraphNode_t hDst) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphKernelNodeCopyAttributes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphKernelNodeCopyAttributes = (cudaError_t (*)(cudaGraphNode_t, cudaGraphNode_t)) dlsym(libcudart_handle, "cudaGraphKernelNodeCopyAttributes");
			fprintf(stderr, "cudaGraphKernelNodeCopyAttributes:%p\n", wrapper_cudaGraphKernelNodeCopyAttributes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphKernelNodeCopyAttributes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphKernelNodeCopyAttributes(hSrc, hDst);
		return retval;
	}
}

