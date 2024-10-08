#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleGetTexRef)(CUtexref *, CUmodule, const char *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod, const char *name) {
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
				fprintf(stderr, "dlsym error for fntion cuModuleGetTexRef():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleGetTexRef)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleGetTexRef = (CUresult (*)(CUtexref *, CUmodule, const char *)) __libc_dlsym(libcuda_handle, "cuModuleGetTexRef");
			fprintf(stderr, "cuModuleGetTexRef:%p\n", original_cuModuleGetTexRef);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleGetTexRef():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleGetTexRef(pTexRef, hmod, name);
		return retval;
	}
}

