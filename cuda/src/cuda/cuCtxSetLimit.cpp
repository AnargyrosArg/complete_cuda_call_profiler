#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxSetLimit)(CUlimit, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxSetLimit(CUlimit limit, size_t value) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSetLimit():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxSetLimit)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxSetLimit = (CUresult (*)(CUlimit, size_t)) __libc_dlsym(libcuda_handle, "cuCtxSetLimit");
			fprintf(stderr, "cuCtxSetLimit:%p\n", original_cuCtxSetLimit);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSetLimit():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxSetLimit(limit, value);
		return retval;
	}
}

