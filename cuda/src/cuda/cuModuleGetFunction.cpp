#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleGetFunction)(CUfunction *, CUmodule, const char *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror = NULL;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleGetFunction():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleGetFunction)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleGetFunction = (CUresult (*)(CUfunction *, CUmodule, const char *)) __libc_dlsym(libcuda_handle, "cuModuleGetFunction");
			fprintf(stderr, "cuModuleGetFunction:%p\n", original_cuModuleGetFunction);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleGetFunction():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleGetFunction(hfunc, hmod, name);
		return retval;
	}
}

