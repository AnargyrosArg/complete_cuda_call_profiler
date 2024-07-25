
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphMemcpyNodeSetParams1D)(cudaGraphNode_t, void *, const void *, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphMemcpyNodeSetParams1D(cudaGraphNode_t node, void *dst, const void *src, size_t count, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphMemcpyNodeSetParams1D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphMemcpyNodeSetParams1D = (cudaError_t (*)(cudaGraphNode_t, void *, const void *, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaGraphMemcpyNodeSetParams1D");
			fprintf(stderr, "cudaGraphMemcpyNodeSetParams1D:%p\n", wrapper_cudaGraphMemcpyNodeSetParams1D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphMemcpyNodeSetParams1D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphMemcpyNodeSetParams1D(node, dst, src, count, kind);
		return retval;
	}
}

