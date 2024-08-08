
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaSetValidDevices)(int *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaSetValidDevices(int *device_arr, int len) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaSetValidDevices)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaSetValidDevices = (cudaError_t (*)(int *, int)) dlsym(libcudart_handle, "cudaSetValidDevices");
			fprintf(stderr, "cudaSetValidDevices:%p\n", wrapper_cudaSetValidDevices);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaSetValidDevices():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaSetValidDevices(device_arr, len);
		return retval;
	}
}

