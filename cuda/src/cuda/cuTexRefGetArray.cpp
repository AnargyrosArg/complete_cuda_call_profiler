#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetArray)(CUarray *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetArray = (CUresult (*)(CUarray *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetArray");
			fprintf(stderr, "cuTexRefGetArray:%p\n", original_cuTexRefGetArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetArray(phArray, hTexRef);
		return retval;
	}
}

