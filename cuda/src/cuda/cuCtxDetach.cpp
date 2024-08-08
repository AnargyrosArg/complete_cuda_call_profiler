#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxDetach)(CUcontext);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxDetach(CUcontext ctx) {
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
				fprintf(stderr, "dlsym error for fntion cuCtxDetach():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxDetach)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxDetach = (CUresult (*)(CUcontext)) __libc_dlsym(libcuda_handle, "cuCtxDetach");
			fprintf(stderr, "cuCtxDetach:%p\n", original_cuCtxDetach);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxDetach():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxDetach(ctx);
		return retval;
	}
}

