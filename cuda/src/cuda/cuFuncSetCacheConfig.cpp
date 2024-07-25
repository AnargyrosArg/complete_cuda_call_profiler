#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuFuncSetCacheConfig)(CUfunction, CUfunc_cache);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetCacheConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuFuncSetCacheConfig)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuFuncSetCacheConfig = (CUresult (*)(CUfunction, CUfunc_cache)) __libc_dlsym(libcuda_handle, "cuFuncSetCacheConfig");
			fprintf(stderr, "cuFuncSetCacheConfig:%p\n", original_cuFuncSetCacheConfig);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFuncSetCacheConfig():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuFuncSetCacheConfig(hfunc, config);
		return retval;
	}
}

