#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemAddressFree)(CUdeviceptr, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemAddressFree(CUdeviceptr ptr, size_t size) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAddressFree():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemAddressFree)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemAddressFree = (CUresult (*)(CUdeviceptr, size_t)) __libc_dlsym(libcuda_handle, "cuMemAddressFree");
			fprintf(stderr, "cuMemAddressFree:%p\n", original_cuMemAddressFree);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAddressFree():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemAddressFree(ptr, size);
		return retval;
	}
}

