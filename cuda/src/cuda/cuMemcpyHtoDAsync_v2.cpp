#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyHtoDAsync_v2)(CUdeviceptr, const void *, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyHtoDAsync_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyHtoDAsync_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyHtoDAsync_v2 = (CUresult (*)(CUdeviceptr, const void *, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemcpyHtoDAsync_v2");
			fprintf(stderr, "cuMemcpyHtoDAsync_v2:%p\n", original_cuMemcpyHtoDAsync_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyHtoDAsync_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyHtoDAsync_v2(dstDevice, srcHost, ByteCount, hStream);
		return retval;
	}
}

