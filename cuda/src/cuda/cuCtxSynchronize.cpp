#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxSynchronize)();
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxSynchronize() {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSynchronize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxSynchronize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxSynchronize = (CUresult (*)()) __libc_dlsym(libcuda_handle, "cuCtxSynchronize");
			fprintf(stderr, "cuCtxSynchronize:%p\n", original_cuCtxSynchronize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSynchronize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxSynchronize();
		return retval;
	}
}

