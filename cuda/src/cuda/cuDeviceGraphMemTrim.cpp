#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGraphMemTrim)(CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGraphMemTrim(CUdevice device) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGraphMemTrim():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGraphMemTrim)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGraphMemTrim = (CUresult (*)(CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGraphMemTrim");
			fprintf(stderr, "cuDeviceGraphMemTrim:%p\n", original_cuDeviceGraphMemTrim);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGraphMemTrim():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGraphMemTrim(device);
		return retval;
	}
}

