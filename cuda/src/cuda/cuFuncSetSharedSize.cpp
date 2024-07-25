#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuFuncSetSharedSize)(CUfunction, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetSharedSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuFuncSetSharedSize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuFuncSetSharedSize = (CUresult (*)(CUfunction, unsigned int)) __libc_dlsym(libcuda_handle, "cuFuncSetSharedSize");
			fprintf(stderr, "cuFuncSetSharedSize:%p\n", original_cuFuncSetSharedSize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetSharedSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuFuncSetSharedSize(hfunc, bytes);
		return retval;
	}
}

