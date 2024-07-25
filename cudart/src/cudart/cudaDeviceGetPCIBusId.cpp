
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetPCIBusId)(char *, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetPCIBusId(char *pciBusId, int len, int device) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetPCIBusId)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetPCIBusId = (cudaError_t (*)(char *, int, int)) dlsym(libcudart_handle, "cudaDeviceGetPCIBusId");
			fprintf(stderr, "cudaDeviceGetPCIBusId:%p\n", wrapper_cudaDeviceGetPCIBusId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetPCIBusId():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetPCIBusId(pciBusId, len, device);
		return retval;
	}
}

