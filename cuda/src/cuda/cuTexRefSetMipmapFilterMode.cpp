#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetMipmapFilterMode)(CUtexref, CUfilter_mode);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetMipmapFilterMode(CUtexref hTexRef, CUfilter_mode fm) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmapFilterMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetMipmapFilterMode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetMipmapFilterMode = (CUresult (*)(CUtexref, CUfilter_mode)) __libc_dlsym(libcuda_handle, "cuTexRefSetMipmapFilterMode");
			fprintf(stderr, "cuTexRefSetMipmapFilterMode:%p\n", original_cuTexRefSetMipmapFilterMode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmapFilterMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetMipmapFilterMode(hTexRef, fm);
		return retval;
	}
}

