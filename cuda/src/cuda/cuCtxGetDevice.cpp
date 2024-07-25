#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxGetDevice)(CUdevice *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxGetDevice(CUdevice *device) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetDevice():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxGetDevice)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxGetDevice = (CUresult (*)(CUdevice *)) __libc_dlsym(libcuda_handle, "cuCtxGetDevice");
			fprintf(stderr, "cuCtxGetDevice:%p\n", original_cuCtxGetDevice);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetDevice():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxGetDevice(device);
		return retval;
	}
}

