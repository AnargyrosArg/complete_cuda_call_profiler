#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetArray)(CUtexref, CUarray, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetArray = (CUresult (*)(CUtexref, CUarray, unsigned int)) __libc_dlsym(libcuda_handle, "cuTexRefSetArray");
			fprintf(stderr, "cuTexRefSetArray:%p\n", original_cuTexRefSetArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetArray(hTexRef, hArray, Flags);
		return retval;
	}
}

