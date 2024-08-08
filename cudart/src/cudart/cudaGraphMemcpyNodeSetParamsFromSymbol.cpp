
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemcpyNodeSetParamsFromSymbol)(cudaGraphNode_t, void *, const void *, size_t, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemcpyNodeSetParamsFromSymbol(cudaGraphNode_t node, void *dst, const void *symbol, size_t count, size_t offset, enum cudaMemcpyKind kind) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemcpyNodeSetParamsFromSymbol)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemcpyNodeSetParamsFromSymbol = (cudaError_t (*)(cudaGraphNode_t, void *, const void *, size_t, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaGraphMemcpyNodeSetParamsFromSymbol");
			fprintf(stderr, "cudaGraphMemcpyNodeSetParamsFromSymbol:%p\n", wrapper_cudaGraphMemcpyNodeSetParamsFromSymbol);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemcpyNodeSetParamsFromSymbol():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemcpyNodeSetParamsFromSymbol(node, dst, symbol, count, offset, kind);
		return retval;
	}
}

