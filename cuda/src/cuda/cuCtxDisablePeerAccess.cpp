#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxDisablePeerAccess)(CUcontext);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxDisablePeerAccess(CUcontext peerContext) {
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
				fprintf(stderr, "dlsym error for fntion cuCtxDisablePeerAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxDisablePeerAccess)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxDisablePeerAccess = (CUresult (*)(CUcontext)) __libc_dlsym(libcuda_handle, "cuCtxDisablePeerAccess");
			fprintf(stderr, "cuCtxDisablePeerAccess:%p\n", original_cuCtxDisablePeerAccess);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxDisablePeerAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxDisablePeerAccess(peerContext);
		return retval;
	}
}

