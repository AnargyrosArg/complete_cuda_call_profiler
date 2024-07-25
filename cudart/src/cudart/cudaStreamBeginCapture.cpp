
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamBeginCapture)(cudaStream_t, enum cudaStreamCaptureMode);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamBeginCapture(cudaStream_t stream, enum cudaStreamCaptureMode mode) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamBeginCapture)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamBeginCapture = (cudaError_t (*)(cudaStream_t, enum cudaStreamCaptureMode)) dlsym(libcudart_handle, "cudaStreamBeginCapture");
			fprintf(stderr, "cudaStreamBeginCapture:%p\n", wrapper_cudaStreamBeginCapture);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamBeginCapture():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamBeginCapture(stream, mode);
		return retval;
	}
}

