
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemFreeNodeGetParams)(cudaGraphNode_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemFreeNodeGetParams(cudaGraphNode_t node, void *dptr_out) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemFreeNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemFreeNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, void *)) dlsym(libcudart_handle, "cudaGraphMemFreeNodeGetParams");
			fprintf(stderr, "cudaGraphMemFreeNodeGetParams:%p\n", wrapper_cudaGraphMemFreeNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemFreeNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemFreeNodeGetParams(node, dptr_out);
		return retval;
	}
}

