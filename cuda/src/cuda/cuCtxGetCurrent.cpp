#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxGetCurrent)(CUcontext *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxGetCurrent(CUcontext *pctx) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetCurrent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxGetCurrent)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxGetCurrent = (CUresult (*)(CUcontext *)) __libc_dlsym(libcuda_handle, "cuCtxGetCurrent");
			fprintf(stderr, "cuCtxGetCurrent:%p\n", original_cuCtxGetCurrent);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetCurrent():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxGetCurrent(pctx);
		return retval;
	}
}

