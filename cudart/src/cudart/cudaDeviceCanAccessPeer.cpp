
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceCanAccessPeer)(int *, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer, int device, int peerDevice) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceCanAccessPeer)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceCanAccessPeer = (cudaError_t (*)(int *, int, int)) dlsym(libcudart_handle, "cudaDeviceCanAccessPeer");
			fprintf(stderr, "cudaDeviceCanAccessPeer:%p\n", wrapper_cudaDeviceCanAccessPeer);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceCanAccessPeer():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceCanAccessPeer(canAccessPeer, device, peerDevice);
		return retval;
	}
}

