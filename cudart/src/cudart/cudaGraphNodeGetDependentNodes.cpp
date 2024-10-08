
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphNodeGetDependentNodes)(cudaGraphNode_t, cudaGraphNode_t *, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphNodeGetDependentNodes(cudaGraphNode_t node, cudaGraphNode_t *pDependentNodes, size_t *pNumDependentNodes) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphNodeGetDependentNodes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphNodeGetDependentNodes = (cudaError_t (*)(cudaGraphNode_t, cudaGraphNode_t *, size_t *)) dlsym(libcudart_handle, "cudaGraphNodeGetDependentNodes");
			fprintf(stderr, "cudaGraphNodeGetDependentNodes:%p\n", wrapper_cudaGraphNodeGetDependentNodes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphNodeGetDependentNodes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphNodeGetDependentNodes(node, pDependentNodes, pNumDependentNodes);
		return retval;
	}
}

