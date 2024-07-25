
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphNodeGetEnabled)(cudaGraphExec_t, cudaGraphNode_t, unsigned int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphNodeGetEnabled(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, unsigned int *isEnabled) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphNodeGetEnabled)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphNodeGetEnabled = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, unsigned int *)) dlsym(libcudart_handle, "cudaGraphNodeGetEnabled");
			fprintf(stderr, "cudaGraphNodeGetEnabled:%p\n", wrapper_cudaGraphNodeGetEnabled);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphNodeGetEnabled():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphNodeGetEnabled(hGraphExec, hNode, isEnabled);
		return retval;
	}
}

