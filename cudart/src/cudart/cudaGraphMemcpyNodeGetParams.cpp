
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemcpyNodeGetParams)(cudaGraphNode_t, struct cudaMemcpy3DParms *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemcpyNodeGetParams(cudaGraphNode_t node, struct cudaMemcpy3DParms *pNodeParams) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemcpyNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemcpyNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaMemcpy3DParms *)) dlsym(libcudart_handle, "cudaGraphMemcpyNodeGetParams");
			fprintf(stderr, "cudaGraphMemcpyNodeGetParams:%p\n", wrapper_cudaGraphMemcpyNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemcpyNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemcpyNodeGetParams(node, pNodeParams);
		return retval;
	}
}

