#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamGetCtx)(CUstream, CUcontext *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamGetCtx(CUstream hStream, CUcontext *pctx) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamGetCtx():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamGetCtx)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamGetCtx = (CUresult (*)(CUstream, CUcontext *)) __libc_dlsym(libcuda_handle, "cuStreamGetCtx");
			fprintf(stderr, "cuStreamGetCtx:%p\n", original_cuStreamGetCtx);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamGetCtx():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamGetCtx(hStream, pctx);
		return retval;
	}
}

