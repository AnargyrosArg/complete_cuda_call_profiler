#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD8Async)(CUdeviceptr, unsigned char, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD8Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD8Async)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD8Async = (CUresult (*)(CUdeviceptr, unsigned char, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemsetD8Async");
			fprintf(stderr, "cuMemsetD8Async:%p\n", original_cuMemsetD8Async);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD8Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD8Async(dstDevice, uc, N, hStream);
		return retval;
	}
}

