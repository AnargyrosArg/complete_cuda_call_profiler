
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphNodeGetType)(cudaGraphNode_t, enum cudaGraphNodeType *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphNodeGetType(cudaGraphNode_t node, enum cudaGraphNodeType *pType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphNodeGetType)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphNodeGetType = (cudaError_t (*)(cudaGraphNode_t, enum cudaGraphNodeType *)) dlsym(libcudart_handle, "cudaGraphNodeGetType");
			fprintf(stderr, "cudaGraphNodeGetType:%p\n", wrapper_cudaGraphNodeGetType);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphNodeGetType():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphNodeGetType(node, pType);
		return retval;
	}
}

