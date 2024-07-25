#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuPointerSetAttribute)(const void *, CUpointer_attribute, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuPointerSetAttribute(const void *value, CUpointer_attribute attribute, CUdeviceptr ptr) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuPointerSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuPointerSetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuPointerSetAttribute = (CUresult (*)(const void *, CUpointer_attribute, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuPointerSetAttribute");
			fprintf(stderr, "cuPointerSetAttribute:%p\n", original_cuPointerSetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuPointerSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuPointerSetAttribute(value, attribute, ptr);
		return retval;
	}
}

