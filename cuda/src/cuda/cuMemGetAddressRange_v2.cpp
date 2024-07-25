#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemGetAddressRange_v2)(CUdeviceptr *, size_t *, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemGetAddressRange_v2(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetAddressRange_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemGetAddressRange_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemGetAddressRange_v2 = (CUresult (*)(CUdeviceptr *, size_t *, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuMemGetAddressRange_v2");
			fprintf(stderr, "cuMemGetAddressRange_v2:%p\n", original_cuMemGetAddressRange_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetAddressRange_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemGetAddressRange_v2(pbase, psize, dptr);
		return retval;
	}
}

