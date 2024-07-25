
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphNodeSetEnabled)(cudaGraphExec_t, cudaGraphNode_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphNodeSetEnabled(cudaGraphExec_t hGraphExec, cudaGraphNode_t hNode, unsigned int isEnabled) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphNodeSetEnabled)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphNodeSetEnabled = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, unsigned int)) dlsym(libcudart_handle, "cudaGraphNodeSetEnabled");
			fprintf(stderr, "cudaGraphNodeSetEnabled:%p\n", wrapper_cudaGraphNodeSetEnabled);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphNodeSetEnabled():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphNodeSetEnabled(hGraphExec, hNode, isEnabled);
		return retval;
	}
}

