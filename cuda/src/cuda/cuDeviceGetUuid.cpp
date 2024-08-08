#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetUuid)(CUuuid *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetUuid(CUuuid *uuid, CUdevice dev) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceGetUuid():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetUuid)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetUuid = (CUresult (*)(CUuuid *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetUuid");
			fprintf(stderr, "cuDeviceGetUuid:%p\n", original_cuDeviceGetUuid);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetUuid():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetUuid(uuid, dev);
		return retval;
	}
}

