#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefDestroy)(CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefDestroy(CUtexref hTexRef) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefDestroy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefDestroy = (CUresult (*)(CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefDestroy");
			fprintf(stderr, "cuTexRefDestroy:%p\n", original_cuTexRefDestroy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefDestroy(hTexRef);
		return retval;
	}
}

