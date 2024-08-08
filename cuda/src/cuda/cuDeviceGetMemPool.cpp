#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetMemPool)(CUmemoryPool *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetMemPool(CUmemoryPool *pool, CUdevice dev) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceGetMemPool():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetMemPool)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetMemPool = (CUresult (*)(CUmemoryPool *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetMemPool");
			fprintf(stderr, "cuDeviceGetMemPool:%p\n", original_cuDeviceGetMemPool);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetMemPool():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetMemPool(pool, dev);
		return retval;
	}
}

