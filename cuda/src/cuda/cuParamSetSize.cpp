#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuParamSetSize)(CUfunction, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuParamSetSize(CUfunction hfunc, unsigned int numbytes) {
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
				fprintf(stderr, "dlsym error for fntion cuParamSetSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuParamSetSize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuParamSetSize = (CUresult (*)(CUfunction, unsigned int)) __libc_dlsym(libcuda_handle, "cuParamSetSize");
			fprintf(stderr, "cuParamSetSize:%p\n", original_cuParamSetSize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuParamSetSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuParamSetSize(hfunc, numbytes);
		return retval;
	}
}

