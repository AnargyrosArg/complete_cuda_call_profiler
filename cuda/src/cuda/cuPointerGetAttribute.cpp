#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuPointerGetAttribute)(void *, CUpointer_attribute, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuPointerGetAttribute(void *data, CUpointer_attribute attribute, CUdeviceptr ptr) {
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
				fprintf(stderr, "dlsym error for fntion cuPointerGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuPointerGetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuPointerGetAttribute = (CUresult (*)(void *, CUpointer_attribute, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuPointerGetAttribute");
			fprintf(stderr, "cuPointerGetAttribute:%p\n", original_cuPointerGetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuPointerGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuPointerGetAttribute(data, attribute, ptr);
		return retval;
	}
}

