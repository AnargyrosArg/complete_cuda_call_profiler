
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetDeviceProperties)(struct cudaDeviceProp *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp *prop, int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetDeviceProperties)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetDeviceProperties = (cudaError_t (*)(struct cudaDeviceProp *, int)) dlsym(libcudart_handle, "cudaGetDeviceProperties");
			fprintf(stderr, "cudaGetDeviceProperties:%p\n", wrapper_cudaGetDeviceProperties);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetDeviceProperties():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetDeviceProperties(prop, device);
		return retval;
	}
}

