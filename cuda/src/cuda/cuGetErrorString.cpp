#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGetErrorString)(CUresult, const char **);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGetErrorString(CUresult error, const char **pStr) {
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
				fprintf(stderr, "dlsym error for fntion cuGetErrorString():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGetErrorString)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGetErrorString = (CUresult (*)(CUresult, const char **)) __libc_dlsym(libcuda_handle, "cuGetErrorString");
			fprintf(stderr, "cuGetErrorString:%p\n", original_cuGetErrorString);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGetErrorString():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGetErrorString(error, pStr);
		return retval;
	}
}

