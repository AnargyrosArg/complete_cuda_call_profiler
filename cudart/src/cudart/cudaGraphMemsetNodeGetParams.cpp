
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemsetNodeGetParams)(cudaGraphNode_t, struct cudaMemsetParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemsetNodeGetParams(cudaGraphNode_t node, struct cudaMemsetParams *pNodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemsetNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemsetNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaMemsetParams *)) dlsym(libcudart_handle, "cudaGraphMemsetNodeGetParams");
			fprintf(stderr, "cudaGraphMemsetNodeGetParams:%p\n", wrapper_cudaGraphMemsetNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemsetNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemsetNodeGetParams(node, pNodeParams);
		return retval;
	}
}

