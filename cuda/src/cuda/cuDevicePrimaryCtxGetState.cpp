#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDevicePrimaryCtxGetState)(CUdevice, unsigned int *, int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int *flags, int *active) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDevicePrimaryCtxGetState():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDevicePrimaryCtxGetState)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDevicePrimaryCtxGetState = (CUresult (*)(CUdevice, unsigned int *, int *)) __libc_dlsym(libcuda_handle, "cuDevicePrimaryCtxGetState");
			fprintf(stderr, "cuDevicePrimaryCtxGetState:%p\n", original_cuDevicePrimaryCtxGetState);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDevicePrimaryCtxGetState():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDevicePrimaryCtxGetState(dev, flags, active);
		return retval;
	}
}

