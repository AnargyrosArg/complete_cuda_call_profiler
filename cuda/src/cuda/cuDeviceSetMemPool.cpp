#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceSetMemPool)(CUdevice, CUmemoryPool);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceSetMemPool(CUdevice dev, CUmemoryPool pool) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceSetMemPool():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceSetMemPool)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceSetMemPool = (CUresult (*)(CUdevice, CUmemoryPool)) __libc_dlsym(libcuda_handle, "cuDeviceSetMemPool");
			fprintf(stderr, "cuDeviceSetMemPool:%p\n", original_cuDeviceSetMemPool);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceSetMemPool():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceSetMemPool(dev, pool);
		return retval;
	}
}

