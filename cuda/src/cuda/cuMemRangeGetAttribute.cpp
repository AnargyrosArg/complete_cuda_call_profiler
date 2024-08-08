#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemRangeGetAttribute)(void *, size_t, CUmem_range_attribute, CUdeviceptr, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemRangeGetAttribute(void *data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count) {
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
				fprintf(stderr, "dlsym error for fntion cuMemRangeGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemRangeGetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemRangeGetAttribute = (CUresult (*)(void *, size_t, CUmem_range_attribute, CUdeviceptr, size_t)) __libc_dlsym(libcuda_handle, "cuMemRangeGetAttribute");
			fprintf(stderr, "cuMemRangeGetAttribute:%p\n", original_cuMemRangeGetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemRangeGetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemRangeGetAttribute(data, dataSize, attribute, devPtr, count);
		return retval;
	}
}

