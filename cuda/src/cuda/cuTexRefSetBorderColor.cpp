#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetBorderColor)(CUtexref, float *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetBorderColor(CUtexref hTexRef, float *pBorderColor) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetBorderColor():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetBorderColor)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetBorderColor = (CUresult (*)(CUtexref, float *)) __libc_dlsym(libcuda_handle, "cuTexRefSetBorderColor");
			fprintf(stderr, "cuTexRefSetBorderColor:%p\n", original_cuTexRefSetBorderColor);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetBorderColor():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetBorderColor(hTexRef, pBorderColor);
		return retval;
	}
}

