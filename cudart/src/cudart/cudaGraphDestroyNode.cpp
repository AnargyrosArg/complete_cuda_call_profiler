
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphDestroyNode)(cudaGraphNode_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphDestroyNode(cudaGraphNode_t node) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphDestroyNode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphDestroyNode = (cudaError_t (*)(cudaGraphNode_t)) dlsym(libcudart_handle, "cudaGraphDestroyNode");
			fprintf(stderr, "cudaGraphDestroyNode:%p\n", wrapper_cudaGraphDestroyNode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphDestroyNode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphDestroyNode(node);
		return retval;
	}
}

