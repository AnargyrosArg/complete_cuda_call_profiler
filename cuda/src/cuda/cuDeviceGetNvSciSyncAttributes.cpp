#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetNvSciSyncAttributes)(void *, CUdevice, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetNvSciSyncAttributes(void *nvSciSyncAttrList, CUdevice dev, int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetNvSciSyncAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetNvSciSyncAttributes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetNvSciSyncAttributes = (CUresult (*)(void *, CUdevice, int)) __libc_dlsym(libcuda_handle, "cuDeviceGetNvSciSyncAttributes");
			fprintf(stderr, "cuDeviceGetNvSciSyncAttributes:%p\n", original_cuDeviceGetNvSciSyncAttributes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetNvSciSyncAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetNvSciSyncAttributes(nvSciSyncAttrList, dev, flags);
		return retval;
	}
}

