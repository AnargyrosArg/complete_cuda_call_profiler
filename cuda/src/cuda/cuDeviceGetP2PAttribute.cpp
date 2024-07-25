#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetP2PAttribute)(int *, CUdevice_P2PAttribute, CUdevice, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetP2PAttribute(int *value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetP2PAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetP2PAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetP2PAttribute = (CUresult (*)(int *, CUdevice_P2PAttribute, CUdevice, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetP2PAttribute");
			fprintf(stderr, "cuDeviceGetP2PAttribute:%p\n", original_cuDeviceGetP2PAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetP2PAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetP2PAttribute(value, attrib, srcDevice, dstDevice);
		return retval;
	}
}

