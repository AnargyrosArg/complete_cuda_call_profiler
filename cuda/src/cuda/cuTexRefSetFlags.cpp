#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetFlags)(CUtexref, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetFlags = (CUresult (*)(CUtexref, unsigned int)) __libc_dlsym(libcuda_handle, "cuTexRefSetFlags");
			fprintf(stderr, "cuTexRefSetFlags:%p\n", original_cuTexRefSetFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetFlags(hTexRef, Flags);
		return retval;
	}
}

