
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphClone)(cudaGraph_t *, cudaGraph_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphClone(cudaGraph_t *pGraphClone, cudaGraph_t originalGraph) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphClone)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphClone = (cudaError_t (*)(cudaGraph_t *, cudaGraph_t)) dlsym(libcudart_handle, "cudaGraphClone");
			fprintf(stderr, "cudaGraphClone:%p\n", wrapper_cudaGraphClone);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphClone():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphClone(pGraphClone, originalGraph);
		return retval;
	}
}

