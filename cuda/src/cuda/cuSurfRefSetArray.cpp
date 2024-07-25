#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuSurfRefSetArray)(CUsurfref, CUarray, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfRefSetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuSurfRefSetArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuSurfRefSetArray = (CUresult (*)(CUsurfref, CUarray, unsigned int)) __libc_dlsym(libcuda_handle, "cuSurfRefSetArray");
			fprintf(stderr, "cuSurfRefSetArray:%p\n", original_cuSurfRefSetArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfRefSetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuSurfRefSetArray(hSurfRef, hArray, Flags);
		return retval;
	}
}

