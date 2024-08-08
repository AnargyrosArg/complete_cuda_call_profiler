#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleLoadFatBinary)(CUmodule *, const void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin) {
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
				fprintf(stderr, "dlsym error for fntion cuModuleLoadFatBinary():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleLoadFatBinary)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleLoadFatBinary = (CUresult (*)(CUmodule *, const void *)) __libc_dlsym(libcuda_handle, "cuModuleLoadFatBinary");
			fprintf(stderr, "cuModuleLoadFatBinary:%p\n", original_cuModuleLoadFatBinary);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleLoadFatBinary():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleLoadFatBinary(module, fatCubin);
		return retval;
	}
}

