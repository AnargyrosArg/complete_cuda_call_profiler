#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetFlags)(unsigned int *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefGetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetFlags = (CUresult (*)(unsigned int *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetFlags");
			fprintf(stderr, "cuTexRefGetFlags:%p\n", original_cuTexRefGetFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetFlags(pFlags, hTexRef);
		return retval;
	}
}

