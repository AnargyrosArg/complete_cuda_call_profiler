
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecMemcpyNodeSetParamsToSymbol)(cudaGraphExec_t, cudaGraphNode_t, const void *, const void *, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecMemcpyNodeSetParamsToSymbol(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, const void *symbol, const void *src, size_t count, size_t offset, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecMemcpyNodeSetParamsToSymbol)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecMemcpyNodeSetParamsToSymbol = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, const void *, const void *, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaGraphExecMemcpyNodeSetParamsToSymbol");
			fprintf(stderr, "cudaGraphExecMemcpyNodeSetParamsToSymbol:%p\n", wrapper_cudaGraphExecMemcpyNodeSetParamsToSymbol);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecMemcpyNodeSetParamsToSymbol():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecMemcpyNodeSetParamsToSymbol(hGraphExec, node, symbol, src, count, offset, kind);
		return retval;
	}
}

