
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemsetNodeSetParams)(cudaGraphNode_t, const struct cudaMemsetParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemsetNodeSetParams(cudaGraphNode_t node, const struct cudaMemsetParams *pNodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemsetNodeSetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemsetNodeSetParams = (cudaError_t (*)(cudaGraphNode_t, const struct cudaMemsetParams *)) dlsym(libcudart_handle, "cudaGraphMemsetNodeSetParams");
			fprintf(stderr, "cudaGraphMemsetNodeSetParams:%p\n", wrapper_cudaGraphMemsetNodeSetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemsetNodeSetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemsetNodeSetParams(node, pNodeParams);
		return retval;
	}
}

