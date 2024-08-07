#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxGetApiVersion)(CUcontext, unsigned int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxGetApiVersion(CUcontext ctx, unsigned int *version) {
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
				fprintf(stderr, "dlsym error for fntion cuCtxGetApiVersion():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxGetApiVersion)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxGetApiVersion = (CUresult (*)(CUcontext, unsigned int *)) __libc_dlsym(libcuda_handle, "cuCtxGetApiVersion");
			fprintf(stderr, "cuCtxGetApiVersion:%p\n", original_cuCtxGetApiVersion);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetApiVersion():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxGetApiVersion(ctx, version);
		return retval;
	}
}

