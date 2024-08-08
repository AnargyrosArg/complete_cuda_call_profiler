#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuParamSetv)(CUfunction, int, void *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes) {
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
				fprintf(stderr, "dlsym error for fntion cuParamSetv():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuParamSetv)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuParamSetv = (CUresult (*)(CUfunction, int, void *, unsigned int)) __libc_dlsym(libcuda_handle, "cuParamSetv");
			fprintf(stderr, "cuParamSetv:%p\n", original_cuParamSetv);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSetv():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuParamSetv(hfunc, offset, ptr, numbytes);
		return retval;
	}
}

