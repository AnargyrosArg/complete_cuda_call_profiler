
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaSetDevice)(int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaSetDevice(int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaSetDevice)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaSetDevice = (cudaError_t (*)(int)) dlsym(libcudart_handle, "cudaSetDevice");
			fprintf(stderr, "cudaSetDevice:%p\n", wrapper_cudaSetDevice);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaSetDevice():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaSetDevice(device);
		return retval;
	}
}

