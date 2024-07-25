#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetAttribute)(int *, CUdevice_attribute, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetAttribute = (CUresult (*)(int *, CUdevice_attribute, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetAttribute");
			fprintf(stderr, "cuDeviceGetAttribute:%p\n", original_cuDeviceGetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetAttribute(pi, attrib, dev);
		return retval;
	}
}

