
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetTexture1DLinearMaxWidth)(size_t *, const struct cudaChannelFormatDesc *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetTexture1DLinearMaxWidth(size_t *maxWidthInElements, const struct cudaChannelFormatDesc *fmtDesc, int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetTexture1DLinearMaxWidth)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetTexture1DLinearMaxWidth = (cudaError_t (*)(size_t *, const struct cudaChannelFormatDesc *, int)) dlsym(libcudart_handle, "cudaDeviceGetTexture1DLinearMaxWidth");
			fprintf(stderr, "cudaDeviceGetTexture1DLinearMaxWidth:%p\n", wrapper_cudaDeviceGetTexture1DLinearMaxWidth);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetTexture1DLinearMaxWidth():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetTexture1DLinearMaxWidth(maxWidthInElements, fmtDesc, device);
		return retval;
	}
}

