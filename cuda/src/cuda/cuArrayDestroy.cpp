#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuArrayDestroy)(CUarray);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuArrayDestroy(CUarray hArray) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuArrayDestroy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuArrayDestroy = (CUresult (*)(CUarray)) __libc_dlsym(libcuda_handle, "cuArrayDestroy");
			fprintf(stderr, "cuArrayDestroy:%p\n", original_cuArrayDestroy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuArrayDestroy(hArray);
		return retval;
	}
}

