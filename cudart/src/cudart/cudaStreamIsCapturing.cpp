
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamIsCapturing)(cudaStream_t, enum cudaStreamCaptureStatus *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamIsCapturing(cudaStream_t stream, enum cudaStreamCaptureStatus *pCaptureStatus) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamIsCapturing)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamIsCapturing = (cudaError_t (*)(cudaStream_t, enum cudaStreamCaptureStatus *)) dlsym(libcudart_handle, "cudaStreamIsCapturing");
			fprintf(stderr, "cudaStreamIsCapturing:%p\n", wrapper_cudaStreamIsCapturing);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamIsCapturing():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamIsCapturing(stream, pCaptureStatus);
		return retval;
	}
}

