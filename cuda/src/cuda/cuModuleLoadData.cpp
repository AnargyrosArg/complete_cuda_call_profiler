#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleLoadData)(CUmodule *, const void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleLoadData(CUmodule *module, const void *image) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleLoadData():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleLoadData)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleLoadData = (CUresult (*)(CUmodule *, const void *)) __libc_dlsym(libcuda_handle, "cuModuleLoadData");
			fprintf(stderr, "cuModuleLoadData:%p\n", original_cuModuleLoadData);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleLoadData():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleLoadData(module, image);
		return retval;
	}
}

