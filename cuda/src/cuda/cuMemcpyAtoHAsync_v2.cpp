#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyAtoHAsync_v2)(void *, CUarray, size_t, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyAtoHAsync_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyAtoHAsync_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyAtoHAsync_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyAtoHAsync_v2 = (CUresult (*)(void *, CUarray, size_t, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemcpyAtoHAsync_v2");
			fprintf(stderr, "cuMemcpyAtoHAsync_v2:%p\n", original_cuMemcpyAtoHAsync_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyAtoHAsync_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyAtoHAsync_v2(dstHost, srcArray, srcOffset, ByteCount, hStream);
		return retval;
	}
}

