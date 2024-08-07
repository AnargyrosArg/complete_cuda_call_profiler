
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamCreateWithPriority)(cudaStream_t *, unsigned int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamCreateWithPriority(cudaStream_t *pStream, unsigned int flags, int priority) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamCreateWithPriority)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamCreateWithPriority = (cudaError_t (*)(cudaStream_t *, unsigned int, int)) dlsym(libcudart_handle, "cudaStreamCreateWithPriority");
			fprintf(stderr, "cudaStreamCreateWithPriority:%p\n", wrapper_cudaStreamCreateWithPriority);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamCreateWithPriority():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamCreateWithPriority(pStream, flags, priority);
		return retval;
	}
}

