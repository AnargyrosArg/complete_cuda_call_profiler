
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphHostNodeGetParams)(cudaGraphNode_t, struct cudaHostNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphHostNodeGetParams(cudaGraphNode_t node, struct cudaHostNodeParams *pNodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphHostNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphHostNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaHostNodeParams *)) dlsym(libcudart_handle, "cudaGraphHostNodeGetParams");
			fprintf(stderr, "cudaGraphHostNodeGetParams:%p\n", wrapper_cudaGraphHostNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphHostNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphHostNodeGetParams(node, pNodeParams);
		return retval;
	}
}

