#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetBorderColor)(float *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetBorderColor(float *pBorderColor, CUtexref hTexRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetBorderColor():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetBorderColor)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetBorderColor = (CUresult (*)(float *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetBorderColor");
			fprintf(stderr, "cuTexRefGetBorderColor:%p\n", original_cuTexRefGetBorderColor);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetBorderColor():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetBorderColor(pBorderColor, hTexRef);
		return retval;
	}
}

