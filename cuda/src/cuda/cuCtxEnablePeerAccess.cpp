#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxEnablePeerAccess)(CUcontext, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags) {
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
				fprintf(stderr, "dlsym error for fntion cuCtxEnablePeerAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxEnablePeerAccess)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxEnablePeerAccess = (CUresult (*)(CUcontext, unsigned int)) __libc_dlsym(libcuda_handle, "cuCtxEnablePeerAccess");
			fprintf(stderr, "cuCtxEnablePeerAccess:%p\n", original_cuCtxEnablePeerAccess);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxEnablePeerAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxEnablePeerAccess(peerContext, Flags);
		return retval;
	}
}

