#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleLoad)(CUmodule *, const char *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleLoad(CUmodule *module, const char *fname) {
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
				fprintf(stderr, "dlsym error for fntion cuModuleLoad():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleLoad)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleLoad = (CUresult (*)(CUmodule *, const char *)) __libc_dlsym(libcuda_handle, "cuModuleLoad");
			fprintf(stderr, "cuModuleLoad:%p\n", original_cuModuleLoad);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleLoad():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleLoad(module, fname);
		return retval;
	}
}

