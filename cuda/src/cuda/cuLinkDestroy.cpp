#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLinkDestroy)(CUlinkState);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLinkDestroy(CUlinkState state) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLinkDestroy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLinkDestroy = (CUresult (*)(CUlinkState)) __libc_dlsym(libcuda_handle, "cuLinkDestroy");
			fprintf(stderr, "cuLinkDestroy:%p\n", original_cuLinkDestroy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLinkDestroy(state);
		return retval;
	}
}

