
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemAllocNodeGetParams)(cudaGraphNode_t, struct cudaMemAllocNodeParams *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemAllocNodeGetParams(cudaGraphNode_t node, struct cudaMemAllocNodeParams *params_out) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemAllocNodeGetParams)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemAllocNodeGetParams = (cudaError_t (*)(cudaGraphNode_t, struct cudaMemAllocNodeParams *)) dlsym(libcudart_handle, "cudaGraphMemAllocNodeGetParams");
			fprintf(stderr, "cudaGraphMemAllocNodeGetParams:%p\n", wrapper_cudaGraphMemAllocNodeGetParams);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemAllocNodeGetParams():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemAllocNodeGetParams(node, params_out);
		return retval;
	}
}

