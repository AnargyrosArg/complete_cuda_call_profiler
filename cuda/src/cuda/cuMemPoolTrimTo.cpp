#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolTrimTo)(CUmemoryPool, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolTrimTo(CUmemoryPool pool, size_t minBytesToKeep) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolTrimTo():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolTrimTo)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolTrimTo = (CUresult (*)(CUmemoryPool, size_t)) __libc_dlsym(libcuda_handle, "cuMemPoolTrimTo");
			fprintf(stderr, "cuMemPoolTrimTo:%p\n", original_cuMemPoolTrimTo);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolTrimTo():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolTrimTo(pool, minBytesToKeep);
		return retval;
	}
}

