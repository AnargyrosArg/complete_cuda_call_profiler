
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetGraphMemAttribute)(int, enum cudaGraphMemAttributeType, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetGraphMemAttribute(int device, enum cudaGraphMemAttributeType attr, void *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetGraphMemAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetGraphMemAttribute = (cudaError_t (*)(int, enum cudaGraphMemAttributeType, void *)) dlsym(libcudart_handle, "cudaDeviceGetGraphMemAttribute");
			fprintf(stderr, "cudaDeviceGetGraphMemAttribute:%p\n", wrapper_cudaDeviceGetGraphMemAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetGraphMemAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetGraphMemAttribute(device, attr, value);
		return retval;
	}
}

