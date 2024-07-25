#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetFormat)(CUarray_format *, int *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetFormat():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetFormat)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetFormat = (CUresult (*)(CUarray_format *, int *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetFormat");
			fprintf(stderr, "cuTexRefGetFormat:%p\n", original_cuTexRefGetFormat);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetFormat():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetFormat(pFormat, pNumChannels, hTexRef);
		return retval;
	}
}

