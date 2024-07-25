#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxSetSharedMemConfig)(CUsharedconfig);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxSetSharedMemConfig(CUsharedconfig config) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSetSharedMemConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxSetSharedMemConfig)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxSetSharedMemConfig = (CUresult (*)(CUsharedconfig)) __libc_dlsym(libcuda_handle, "cuCtxSetSharedMemConfig");
			fprintf(stderr, "cuCtxSetSharedMemConfig:%p\n", original_cuCtxSetSharedMemConfig);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSetSharedMemConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxSetSharedMemConfig(config);
		return retval;
	}
}

