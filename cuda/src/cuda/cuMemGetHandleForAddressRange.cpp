#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemGetHandleForAddressRange)(void *, CUdeviceptr, size_t, CUmemRangeHandleType, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemGetHandleForAddressRange(void *handle, CUdeviceptr dptr, size_t size, CUmemRangeHandleType handleType, unsigned long long flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetHandleForAddressRange():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemGetHandleForAddressRange)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemGetHandleForAddressRange = (CUresult (*)(void *, CUdeviceptr, size_t, CUmemRangeHandleType, unsigned long long)) __libc_dlsym(libcuda_handle, "cuMemGetHandleForAddressRange");
			fprintf(stderr, "cuMemGetHandleForAddressRange:%p\n", original_cuMemGetHandleForAddressRange);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetHandleForAddressRange():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemGetHandleForAddressRange(handle, dptr, size, handleType, flags);
		return retval;
	}
}

