
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamGetPriority)(cudaStream_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamGetPriority(cudaStream_t hStream, int *priority) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamGetPriority)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamGetPriority = (cudaError_t (*)(cudaStream_t, int *)) dlsym(libcudart_handle, "cudaStreamGetPriority");
			fprintf(stderr, "cudaStreamGetPriority:%p\n", wrapper_cudaStreamGetPriority);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamGetPriority():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamGetPriority(hStream, priority);
		return retval;
	}
}

