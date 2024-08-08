#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetLuid)(char *, unsigned int *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetLuid(char *luid, unsigned int *deviceNodeMask, CUdevice dev) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetLuid():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetLuid)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetLuid = (CUresult (*)(char *, unsigned int *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetLuid");
			fprintf(stderr, "cuDeviceGetLuid:%p\n", original_cuDeviceGetLuid);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetLuid():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetLuid(luid, deviceNodeMask, dev);
		return retval;
	}
}

