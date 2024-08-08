
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphCreate)(cudaGraph_t *, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphCreate(cudaGraph_t *pGraph, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphCreate)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphCreate = (cudaError_t (*)(cudaGraph_t *, unsigned int)) dlsym(libcudart_handle, "cudaGraphCreate");
			fprintf(stderr, "cudaGraphCreate:%p\n", wrapper_cudaGraphCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphCreate(pGraph, flags);
		return retval;
	}
}

