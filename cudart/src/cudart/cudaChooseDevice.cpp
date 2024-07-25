
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaChooseDevice)(int *, const struct cudaDeviceProp *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaChooseDevice(int *device, const struct cudaDeviceProp *prop) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaChooseDevice)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaChooseDevice = (cudaError_t (*)(int *, const struct cudaDeviceProp *)) dlsym(libcudart_handle, "cudaChooseDevice");
			fprintf(stderr, "cudaChooseDevice:%p\n", wrapper_cudaChooseDevice);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaChooseDevice():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaChooseDevice(device, prop);
		return retval;
	}
}

