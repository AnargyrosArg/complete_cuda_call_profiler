#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuFuncSetAttribute)(CUfunction, CUfunction_attribute, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value) {
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
				fprintf(stderr, "dlsym error for fntion cuFuncSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuFuncSetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuFuncSetAttribute = (CUresult (*)(CUfunction, CUfunction_attribute, int)) __libc_dlsym(libcuda_handle, "cuFuncSetAttribute");
			fprintf(stderr, "cuFuncSetAttribute:%p\n", original_cuFuncSetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuFuncSetAttribute(hfunc, attrib, value);
		return retval;
	}
}

