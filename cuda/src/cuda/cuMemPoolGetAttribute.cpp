#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolGetAttribute)(CUmemoryPool, CUmemPool_attribute, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolGetAttribute(CUmemoryPool pool, CUmemPool_attribute attr, void *value) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolGetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolGetAttribute = (CUresult (*)(CUmemoryPool, CUmemPool_attribute, void *)) __libc_dlsym(libcuda_handle, "cuMemPoolGetAttribute");
			fprintf(stderr, "cuMemPoolGetAttribute:%p\n", original_cuMemPoolGetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolGetAttribute(pool, attr, value);
		return retval;
	}
}

