#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuParamSetf)(CUfunction, int, float);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuParamSetf(CUfunction hfunc, int offset, float value) {
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
				fprintf(stderr, "dlsym error for fntion cuParamSetf():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuParamSetf)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuParamSetf = (CUresult (*)(CUfunction, int, float)) __libc_dlsym(libcuda_handle, "cuParamSetf");
			fprintf(stderr, "cuParamSetf:%p\n", original_cuParamSetf);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSetf():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuParamSetf(hfunc, offset, value);
		return retval;
	}
}

