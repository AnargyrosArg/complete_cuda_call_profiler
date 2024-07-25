#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolGetAccess)(CUmemAccess_flags *, CUmemoryPool, CUmemLocation *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolGetAccess(CUmemAccess_flags *flags, CUmemoryPool memPool, CUmemLocation *location) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolGetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolGetAccess)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolGetAccess = (CUresult (*)(CUmemAccess_flags *, CUmemoryPool, CUmemLocation *)) __libc_dlsym(libcuda_handle, "cuMemPoolGetAccess");
			fprintf(stderr, "cuMemPoolGetAccess:%p\n", original_cuMemPoolGetAccess);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolGetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolGetAccess(flags, memPool, location);
		return retval;
	}
}

