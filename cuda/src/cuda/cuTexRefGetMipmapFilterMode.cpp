#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetMipmapFilterMode)(CUfilter_mode *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetMipmapFilterMode(CUfilter_mode *pfm, CUtexref hTexRef) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmapFilterMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetMipmapFilterMode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetMipmapFilterMode = (CUresult (*)(CUfilter_mode *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetMipmapFilterMode");
			fprintf(stderr, "cuTexRefGetMipmapFilterMode:%p\n", original_cuTexRefGetMipmapFilterMode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmapFilterMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetMipmapFilterMode(pfm, hTexRef);
		return retval;
	}
}

