
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceDisablePeerAccess)(int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceDisablePeerAccess(int peerDevice) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceDisablePeerAccess)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceDisablePeerAccess = (cudaError_t (*)(int)) dlsym(libcudart_handle, "cudaDeviceDisablePeerAccess");
			fprintf(stderr, "cudaDeviceDisablePeerAccess:%p\n", wrapper_cudaDeviceDisablePeerAccess);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceDisablePeerAccess():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceDisablePeerAccess(peerDevice);
		return retval;
	}
}

