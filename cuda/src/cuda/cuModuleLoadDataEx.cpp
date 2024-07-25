#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleLoadDataEx)(CUmodule *, const void *, unsigned int, CUjit_option *, void **);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleLoadDataEx():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleLoadDataEx)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleLoadDataEx = (CUresult (*)(CUmodule *, const void *, unsigned int, CUjit_option *, void **)) __libc_dlsym(libcuda_handle, "cuModuleLoadDataEx");
			fprintf(stderr, "cuModuleLoadDataEx:%p\n", original_cuModuleLoadDataEx);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleLoadDataEx():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleLoadDataEx(module, image, numOptions, options, optionValues);
		return retval;
	}
}

