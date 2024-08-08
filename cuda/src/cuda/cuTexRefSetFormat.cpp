#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetFormat)(CUtexref, CUarray_format, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefSetFormat():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetFormat)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetFormat = (CUresult (*)(CUtexref, CUarray_format, int)) __libc_dlsym(libcuda_handle, "cuTexRefSetFormat");
			fprintf(stderr, "cuTexRefSetFormat:%p\n", original_cuTexRefSetFormat);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetFormat():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetFormat(hTexRef, fmt, NumPackedComponents);
		return retval;
	}
}

