
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetByPCIBusId)(int *, const char *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetByPCIBusId(int *device, const char *pciBusId) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetByPCIBusId)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetByPCIBusId = (cudaError_t (*)(int *, const char *)) dlsym(libcudart_handle, "cudaDeviceGetByPCIBusId");
			fprintf(stderr, "cudaDeviceGetByPCIBusId:%p\n", wrapper_cudaDeviceGetByPCIBusId);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetByPCIBusId():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetByPCIBusId(device, pciBusId);
		return retval;
	}
}

