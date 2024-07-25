
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphInstantiateWithFlags)(cudaGraphExec_t *, cudaGraph_t, unsigned long long);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphInstantiateWithFlags(cudaGraphExec_t *pGraphExec, cudaGraph_t graph, unsigned long long flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphInstantiateWithFlags)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphInstantiateWithFlags = (cudaError_t (*)(cudaGraphExec_t *, cudaGraph_t, unsigned long long)) dlsym(libcudart_handle, "cudaGraphInstantiateWithFlags");
			fprintf(stderr, "cudaGraphInstantiateWithFlags:%p\n", wrapper_cudaGraphInstantiateWithFlags);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphInstantiateWithFlags():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphInstantiateWithFlags(pGraphExec, graph, flags);
		return retval;
	}
}

