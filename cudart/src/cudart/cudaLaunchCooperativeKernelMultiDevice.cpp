
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaLaunchCooperativeKernelMultiDevice)(struct cudaLaunchParams *, unsigned int, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaLaunchCooperativeKernelMultiDevice(struct cudaLaunchParams *launchParamsList, unsigned int numDevices, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaLaunchCooperativeKernelMultiDevice)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaLaunchCooperativeKernelMultiDevice = (cudaError_t (*)(struct cudaLaunchParams *, unsigned int, unsigned int)) dlsym(libcudart_handle, "cudaLaunchCooperativeKernelMultiDevice");
			fprintf(stderr, "cudaLaunchCooperativeKernelMultiDevice:%p\n", wrapper_cudaLaunchCooperativeKernelMultiDevice);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaLaunchCooperativeKernelMultiDevice():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaLaunchCooperativeKernelMultiDevice(launchParamsList, numDevices, flags);
		return retval;
	}
}

