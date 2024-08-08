#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDriverGetVersion)(int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDriverGetVersion(int *driverVersion) {
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
				fprintf(stderr, "dlsym error for fntion cuDriverGetVersion():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDriverGetVersion)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDriverGetVersion = (CUresult (*)(int *)) __libc_dlsym(libcuda_handle, "cuDriverGetVersion");
			fprintf(stderr, "cuDriverGetVersion:%p\n", original_cuDriverGetVersion);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDriverGetVersion():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDriverGetVersion(driverVersion);
		return retval;
	}
}

