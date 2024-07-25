#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxCreate_v2)(CUcontext *, unsigned int, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxCreate_v2(CUcontext *pctx, unsigned int flags, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxCreate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxCreate_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxCreate_v2 = (CUresult (*)(CUcontext *, unsigned int, CUdevice)) __libc_dlsym(libcuda_handle, "cuCtxCreate_v2");
			fprintf(stderr, "cuCtxCreate_v2:%p\n", original_cuCtxCreate_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxCreate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxCreate_v2(pctx, flags, dev);
		return retval;
	}
}

