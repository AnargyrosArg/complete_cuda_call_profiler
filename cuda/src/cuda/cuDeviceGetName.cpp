#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetName)(char *, int, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetName(char *name, int len, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetName():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetName)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetName = (CUresult (*)(char *, int, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetName");
			fprintf(stderr, "cuDeviceGetName:%p\n", original_cuDeviceGetName);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetName():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetName(name, len, dev);
		return retval;
	}
}

