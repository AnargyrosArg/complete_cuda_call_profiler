
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaSetDoubleForDevice)(double *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaSetDoubleForDevice(double *d) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaSetDoubleForDevice)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaSetDoubleForDevice = (cudaError_t (*)(double *)) dlsym(libcudart_handle, "cudaSetDoubleForDevice");
			fprintf(stderr, "cudaSetDoubleForDevice:%p\n", wrapper_cudaSetDoubleForDevice);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaSetDoubleForDevice():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaSetDoubleForDevice(d);
		return retval;
	}
}

