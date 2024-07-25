#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetProperties)(CUdevprop *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetProperties(CUdevprop *prop, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetProperties():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetProperties)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetProperties = (CUresult (*)(CUdevprop *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetProperties");
			fprintf(stderr, "cuDeviceGetProperties:%p\n", original_cuDeviceGetProperties);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetProperties():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetProperties(prop, dev);
		return retval;
	}
}

