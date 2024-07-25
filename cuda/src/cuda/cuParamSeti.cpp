#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuParamSeti)(CUfunction, int, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuParamSeti(CUfunction hfunc, int offset, unsigned int value) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSeti():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuParamSeti)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuParamSeti = (CUresult (*)(CUfunction, int, unsigned int)) __libc_dlsym(libcuda_handle, "cuParamSeti");
			fprintf(stderr, "cuParamSeti:%p\n", original_cuParamSeti);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSeti():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuParamSeti(hfunc, offset, value);
		return retval;
	}
}

