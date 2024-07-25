#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuSurfRefGetArray)(CUarray *, CUsurfref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfRefGetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuSurfRefGetArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuSurfRefGetArray = (CUresult (*)(CUarray *, CUsurfref)) __libc_dlsym(libcuda_handle, "cuSurfRefGetArray");
			fprintf(stderr, "cuSurfRefGetArray:%p\n", original_cuSurfRefGetArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfRefGetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuSurfRefGetArray(phArray, hSurfRef);
		return retval;
	}
}

