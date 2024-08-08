
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceEnablePeerAccess)(int, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceEnablePeerAccess(int peerDevice, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceEnablePeerAccess)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceEnablePeerAccess = (cudaError_t (*)(int, unsigned int)) dlsym(libcudart_handle, "cudaDeviceEnablePeerAccess");
			fprintf(stderr, "cudaDeviceEnablePeerAccess:%p\n", wrapper_cudaDeviceEnablePeerAccess);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceEnablePeerAccess():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceEnablePeerAccess(peerDevice, flags);
		return retval;
	}
}

