#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDevicePrimaryCtxRetain)(CUcontext *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDevicePrimaryCtxRetain(CUcontext *pctx, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDevicePrimaryCtxRetain():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDevicePrimaryCtxRetain)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDevicePrimaryCtxRetain = (CUresult (*)(CUcontext *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDevicePrimaryCtxRetain");
			fprintf(stderr, "cuDevicePrimaryCtxRetain:%p\n", original_cuDevicePrimaryCtxRetain);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDevicePrimaryCtxRetain():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDevicePrimaryCtxRetain(pctx, dev);
		return retval;
	}
}

