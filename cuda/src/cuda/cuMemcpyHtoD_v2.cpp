#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyHtoD_v2)(CUdeviceptr, const void *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyHtoD_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyHtoD_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyHtoD_v2 = (CUresult (*)(CUdeviceptr, const void *, size_t)) __libc_dlsym(libcuda_handle, "cuMemcpyHtoD_v2");
			fprintf(stderr, "cuMemcpyHtoD_v2:%p\n", original_cuMemcpyHtoD_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyHtoD_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyHtoD_v2(dstDevice, srcHost, ByteCount);
		return retval;
	}
}

