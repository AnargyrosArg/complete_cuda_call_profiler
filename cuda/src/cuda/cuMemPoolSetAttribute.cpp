#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolSetAttribute)(CUmemoryPool, CUmemPool_attribute, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolSetAttribute(CUmemoryPool pool, CUmemPool_attribute attr, void *value) {
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
				fprintf(stderr, "dlsym error for fntion cuMemPoolSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolSetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolSetAttribute = (CUresult (*)(CUmemoryPool, CUmemPool_attribute, void *)) __libc_dlsym(libcuda_handle, "cuMemPoolSetAttribute");
			fprintf(stderr, "cuMemPoolSetAttribute:%p\n", original_cuMemPoolSetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolSetAttribute(pool, attr, value);
		return retval;
	}
}

