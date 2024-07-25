
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphDebugDotPrint)(cudaGraph_t, const char *, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphDebugDotPrint(cudaGraph_t graph, const char *path, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphDebugDotPrint)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphDebugDotPrint = (cudaError_t (*)(cudaGraph_t, const char *, unsigned int)) dlsym(libcudart_handle, "cudaGraphDebugDotPrint");
			fprintf(stderr, "cudaGraphDebugDotPrint:%p\n", wrapper_cudaGraphDebugDotPrint);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphDebugDotPrint():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphDebugDotPrint(graph, path, flags);
		return retval;
	}
}

