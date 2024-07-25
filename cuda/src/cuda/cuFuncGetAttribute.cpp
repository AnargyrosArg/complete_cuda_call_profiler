#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuFuncGetAttribute)(int *, CUfunction_attribute, CUfunction);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuFuncGetAttribute(int *pi, CUfunction_attribute attrib, CUfunction hfunc) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuFuncGetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuFuncGetAttribute = (CUresult (*)(int *, CUfunction_attribute, CUfunction)) __libc_dlsym(libcuda_handle, "cuFuncGetAttribute");
			fprintf(stderr, "cuFuncGetAttribute:%p\n", original_cuFuncGetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuFuncGetAttribute(pi, attrib, hfunc);
		return retval;
	}
}

