#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyHtoA_v2)(CUarray, size_t, const void *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyHtoA_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyHtoA_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyHtoA_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyHtoA_v2 = (CUresult (*)(CUarray, size_t, const void *, size_t)) __libc_dlsym(libcuda_handle, "cuMemcpyHtoA_v2");
			fprintf(stderr, "cuMemcpyHtoA_v2:%p\n", original_cuMemcpyHtoA_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyHtoA_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyHtoA_v2(dstArray, dstOffset, srcHost, ByteCount);
		return retval;
	}
}

