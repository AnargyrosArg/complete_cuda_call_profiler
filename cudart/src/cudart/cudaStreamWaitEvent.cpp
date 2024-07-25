
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamWaitEvent)(cudaStream_t, cudaEvent_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamWaitEvent)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamWaitEvent = (cudaError_t (*)(cudaStream_t, cudaEvent_t, unsigned int)) dlsym(libcudart_handle, "cudaStreamWaitEvent");
			fprintf(stderr, "cudaStreamWaitEvent:%p\n", wrapper_cudaStreamWaitEvent);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamWaitEvent():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamWaitEvent(stream, event, flags);
		return retval;
	}
}

