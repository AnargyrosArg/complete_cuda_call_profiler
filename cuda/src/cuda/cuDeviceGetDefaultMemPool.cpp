#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetDefaultMemPool)(CUmemoryPool *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetDefaultMemPool(CUmemoryPool *pool_out, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetDefaultMemPool():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetDefaultMemPool)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetDefaultMemPool = (CUresult (*)(CUmemoryPool *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetDefaultMemPool");
			fprintf(stderr, "cuDeviceGetDefaultMemPool:%p\n", original_cuDeviceGetDefaultMemPool);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetDefaultMemPool():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetDefaultMemPool(pool_out, dev);
		return retval;
	}
}

