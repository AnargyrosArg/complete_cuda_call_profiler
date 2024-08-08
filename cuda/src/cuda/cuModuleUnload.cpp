#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleUnload)(CUmodule);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleUnload(CUmodule hmod) {
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
				fprintf(stderr, "dlsym error for fntion cuModuleUnload():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleUnload)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleUnload = (CUresult (*)(CUmodule)) __libc_dlsym(libcuda_handle, "cuModuleUnload");
			fprintf(stderr, "cuModuleUnload:%p\n", original_cuModuleUnload);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleUnload():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleUnload(hmod);
		return retval;
	}
}

