
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetSharedMemConfig)(enum cudaSharedMemConfig *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetSharedMemConfig(enum cudaSharedMemConfig *pConfig) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetSharedMemConfig)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetSharedMemConfig = (cudaError_t (*)(enum cudaSharedMemConfig *)) dlsym(libcudart_handle, "cudaDeviceGetSharedMemConfig");
			fprintf(stderr, "cudaDeviceGetSharedMemConfig:%p\n", wrapper_cudaDeviceGetSharedMemConfig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetSharedMemConfig():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetSharedMemConfig(pConfig);
		return retval;
	}
}

