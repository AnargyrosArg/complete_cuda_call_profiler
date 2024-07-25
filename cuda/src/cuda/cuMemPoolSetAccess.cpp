#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolSetAccess)(CUmemoryPool, const CUmemAccessDesc *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolSetAccess(CUmemoryPool pool, const CUmemAccessDesc *map, size_t count) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolSetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolSetAccess)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolSetAccess = (CUresult (*)(CUmemoryPool, const CUmemAccessDesc *, size_t)) __libc_dlsym(libcuda_handle, "cuMemPoolSetAccess");
			fprintf(stderr, "cuMemPoolSetAccess:%p\n", original_cuMemPoolSetAccess);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolSetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolSetAccess(pool, map, count);
		return retval;
	}
}

