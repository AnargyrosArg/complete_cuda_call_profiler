#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuFuncSetBlockShape)(CUfunction, int, int, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetBlockShape():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuFuncSetBlockShape)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuFuncSetBlockShape = (CUresult (*)(CUfunction, int, int, int)) __libc_dlsym(libcuda_handle, "cuFuncSetBlockShape");
			fprintf(stderr, "cuFuncSetBlockShape:%p\n", original_cuFuncSetBlockShape);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetBlockShape():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuFuncSetBlockShape(hfunc, x, y, z);
		return retval;
	}
}

