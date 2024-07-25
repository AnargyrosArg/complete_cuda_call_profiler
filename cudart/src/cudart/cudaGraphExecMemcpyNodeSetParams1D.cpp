
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphExecMemcpyNodeSetParams1D)(cudaGraphExec_t, cudaGraphNode_t, void *, const void *, size_t, enum cudaMemcpyKind);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphExecMemcpyNodeSetParams1D(cudaGraphExec_t hGraphExec, cudaGraphNode_t node, void *dst, const void *src, size_t count, enum cudaMemcpyKind kind) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphExecMemcpyNodeSetParams1D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphExecMemcpyNodeSetParams1D = (cudaError_t (*)(cudaGraphExec_t, cudaGraphNode_t, void *, const void *, size_t, enum cudaMemcpyKind)) dlsym(libcudart_handle, "cudaGraphExecMemcpyNodeSetParams1D");
			fprintf(stderr, "cudaGraphExecMemcpyNodeSetParams1D:%p\n", wrapper_cudaGraphExecMemcpyNodeSetParams1D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphExecMemcpyNodeSetParams1D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphExecMemcpyNodeSetParams1D(hGraphExec, node, dst, src, count, kind);
		return retval;
	}
}

