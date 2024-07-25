
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamGetCaptureInfo)(cudaStream_t, enum cudaStreamCaptureStatus *, unsigned long long *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamGetCaptureInfo(cudaStream_t stream, enum cudaStreamCaptureStatus *pCaptureStatus, unsigned long long *pId) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamGetCaptureInfo)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamGetCaptureInfo = (cudaError_t (*)(cudaStream_t, enum cudaStreamCaptureStatus *, unsigned long long *)) dlsym(libcudart_handle, "cudaStreamGetCaptureInfo");
			fprintf(stderr, "cudaStreamGetCaptureInfo:%p\n", wrapper_cudaStreamGetCaptureInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamGetCaptureInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamGetCaptureInfo(stream, pCaptureStatus, pId);
		return retval;
	}
}

