
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetP2PAttribute)(int *, enum cudaDeviceP2PAttr, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetP2PAttribute(int *value, enum cudaDeviceP2PAttr attr, int srcDevice, int dstDevice) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetP2PAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetP2PAttribute = (cudaError_t (*)(int *, enum cudaDeviceP2PAttr, int, int)) dlsym(libcudart_handle, "cudaDeviceGetP2PAttribute");
			fprintf(stderr, "cudaDeviceGetP2PAttribute:%p\n", wrapper_cudaDeviceGetP2PAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetP2PAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetP2PAttribute(value, attr, srcDevice, dstDevice);
		return retval;
	}
}

