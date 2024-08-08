
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDriverGetVersion)(int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDriverGetVersion(int *driverVersion) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDriverGetVersion)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDriverGetVersion = (cudaError_t (*)(int *)) dlsym(libcudart_handle, "cudaDriverGetVersion");
			fprintf(stderr, "cudaDriverGetVersion:%p\n", wrapper_cudaDriverGetVersion);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDriverGetVersion():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDriverGetVersion(driverVersion);
		return retval;
	}
}

