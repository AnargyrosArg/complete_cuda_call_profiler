
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaThreadExchangeStreamCaptureMode)(enum cudaStreamCaptureMode *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaThreadExchangeStreamCaptureMode(enum cudaStreamCaptureMode *mode) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaThreadExchangeStreamCaptureMode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaThreadExchangeStreamCaptureMode = (cudaError_t (*)(enum cudaStreamCaptureMode *)) dlsym(libcudart_handle, "cudaThreadExchangeStreamCaptureMode");
			fprintf(stderr, "cudaThreadExchangeStreamCaptureMode:%p\n", wrapper_cudaThreadExchangeStreamCaptureMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaThreadExchangeStreamCaptureMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaThreadExchangeStreamCaptureMode(mode);
		return retval;
	}
}

