#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxCreate_v3)(CUcontext *, CUexecAffinityParam *, int, unsigned int, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxCreate_v3(CUcontext *pctx, CUexecAffinityParam *paramsArray, int numParams, unsigned int flags, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxCreate_v3():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxCreate_v3)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxCreate_v3 = (CUresult (*)(CUcontext *, CUexecAffinityParam *, int, unsigned int, CUdevice)) __libc_dlsym(libcuda_handle, "cuCtxCreate_v3");
			fprintf(stderr, "cuCtxCreate_v3:%p\n", original_cuCtxCreate_v3);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxCreate_v3():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxCreate_v3(pctx, paramsArray, numParams, flags, dev);
		return retval;
	}
}

