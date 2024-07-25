#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLaunchCooperativeKernelMultiDevice)(CUDA_LAUNCH_PARAMS *, unsigned int, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLaunchCooperativeKernelMultiDevice():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLaunchCooperativeKernelMultiDevice)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLaunchCooperativeKernelMultiDevice = (CUresult (*)(CUDA_LAUNCH_PARAMS *, unsigned int, unsigned int)) __libc_dlsym(libcuda_handle, "cuLaunchCooperativeKernelMultiDevice");
			fprintf(stderr, "cuLaunchCooperativeKernelMultiDevice:%p\n", original_cuLaunchCooperativeKernelMultiDevice);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLaunchCooperativeKernelMultiDevice():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLaunchCooperativeKernelMultiDevice(launchParamsList, numDevices, flags);
		return retval;
	}
}

