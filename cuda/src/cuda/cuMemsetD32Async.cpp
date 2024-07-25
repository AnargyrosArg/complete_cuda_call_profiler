#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD32Async)(CUdeviceptr, unsigned int, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD32Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD32Async)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD32Async = (CUresult (*)(CUdeviceptr, unsigned int, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemsetD32Async");
			fprintf(stderr, "cuMemsetD32Async:%p\n", original_cuMemsetD32Async);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD32Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD32Async(dstDevice, ui, N, hStream);
		return retval;
	}
}

