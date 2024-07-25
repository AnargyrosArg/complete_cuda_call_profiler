#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuParamSetTexRef)(CUfunction, int, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSetTexRef():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuParamSetTexRef)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuParamSetTexRef = (CUresult (*)(CUfunction, int, CUtexref)) __libc_dlsym(libcuda_handle, "cuParamSetTexRef");
			fprintf(stderr, "cuParamSetTexRef:%p\n", original_cuParamSetTexRef);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSetTexRef():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuParamSetTexRef(hfunc, texunit, hTexRef);
		return retval;
	}
}

