#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyAsync)(CUdeviceptr, CUdeviceptr, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyAsync = (CUresult (*)(CUdeviceptr, CUdeviceptr, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemcpyAsync");
			fprintf(stderr, "cuMemcpyAsync:%p\n", original_cuMemcpyAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyAsync(dst, src, ByteCount, hStream);
		return retval;
	}
}

