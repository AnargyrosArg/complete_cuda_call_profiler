#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxGetSharedMemConfig)(CUsharedconfig *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxGetSharedMemConfig(CUsharedconfig *pConfig) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetSharedMemConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxGetSharedMemConfig)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxGetSharedMemConfig = (CUresult (*)(CUsharedconfig *)) __libc_dlsym(libcuda_handle, "cuCtxGetSharedMemConfig");
			fprintf(stderr, "cuCtxGetSharedMemConfig:%p\n", original_cuCtxGetSharedMemConfig);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetSharedMemConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxGetSharedMemConfig(pConfig);
		return retval;
	}
}

