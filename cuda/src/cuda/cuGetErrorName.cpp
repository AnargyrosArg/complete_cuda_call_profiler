#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGetErrorName)(CUresult, const char **);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGetErrorName(CUresult error, const char **pStr) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGetErrorName():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGetErrorName)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGetErrorName = (CUresult (*)(CUresult, const char **)) __libc_dlsym(libcuda_handle, "cuGetErrorName");
			fprintf(stderr, "cuGetErrorName:%p\n", original_cuGetErrorName);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGetErrorName():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGetErrorName(error, pStr);
		return retval;
	}
}

