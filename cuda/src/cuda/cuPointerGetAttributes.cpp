#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuPointerGetAttributes)(unsigned int, CUpointer_attribute *, void **, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute *attributes, void **data, CUdeviceptr ptr) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuPointerGetAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuPointerGetAttributes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuPointerGetAttributes = (CUresult (*)(unsigned int, CUpointer_attribute *, void **, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuPointerGetAttributes");
			fprintf(stderr, "cuPointerGetAttributes:%p\n", original_cuPointerGetAttributes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuPointerGetAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuPointerGetAttributes(numAttributes, attributes, data, ptr);
		return retval;
	}
}
