#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetFilterMode)(CUtexref, CUfilter_mode);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetFilterMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetFilterMode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetFilterMode = (CUresult (*)(CUtexref, CUfilter_mode)) __libc_dlsym(libcuda_handle, "cuTexRefSetFilterMode");
			fprintf(stderr, "cuTexRefSetFilterMode:%p\n", original_cuTexRefSetFilterMode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetFilterMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetFilterMode(hTexRef, fm);
		return retval;
	}
}

