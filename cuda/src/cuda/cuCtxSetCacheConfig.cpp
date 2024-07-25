#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxSetCacheConfig)(CUfunc_cache);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxSetCacheConfig(CUfunc_cache config) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSetCacheConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxSetCacheConfig)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxSetCacheConfig = (CUresult (*)(CUfunc_cache)) __libc_dlsym(libcuda_handle, "cuCtxSetCacheConfig");
			fprintf(stderr, "cuCtxSetCacheConfig:%p\n", original_cuCtxSetCacheConfig);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxSetCacheConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxSetCacheConfig(config);
		return retval;
	}
}
