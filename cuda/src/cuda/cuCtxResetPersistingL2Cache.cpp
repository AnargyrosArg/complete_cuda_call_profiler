#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxResetPersistingL2Cache)();
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxResetPersistingL2Cache() {
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
				fprintf(stderr, "dlsym error for fntion cuCtxResetPersistingL2Cache():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxResetPersistingL2Cache)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxResetPersistingL2Cache = (CUresult (*)()) __libc_dlsym(libcuda_handle, "cuCtxResetPersistingL2Cache");
			fprintf(stderr, "cuCtxResetPersistingL2Cache:%p\n", original_cuCtxResetPersistingL2Cache);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxResetPersistingL2Cache():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxResetPersistingL2Cache();
		return retval;
	}
}

