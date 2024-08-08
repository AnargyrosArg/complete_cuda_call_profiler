
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphInstantiate)(cudaGraphExec_t *, cudaGraph_t, cudaGraphNode_t *, char *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphInstantiate(cudaGraphExec_t *pGraphExec, cudaGraph_t graph, cudaGraphNode_t *pErrorNode, char *pLogBuffer, size_t bufferSize) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphInstantiate)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphInstantiate = (cudaError_t (*)(cudaGraphExec_t *, cudaGraph_t, cudaGraphNode_t *, char *, size_t)) dlsym(libcudart_handle, "cudaGraphInstantiate");
			fprintf(stderr, "cudaGraphInstantiate:%p\n", wrapper_cudaGraphInstantiate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphInstantiate():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphInstantiate(pGraphExec, graph, pErrorNode, pLogBuffer, bufferSize);
		return retval;
	}
}

