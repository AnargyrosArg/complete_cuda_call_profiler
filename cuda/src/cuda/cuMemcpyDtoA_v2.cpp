#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyDtoA_v2)(CUarray, size_t, CUdeviceptr, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyDtoA_v2(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyDtoA_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyDtoA_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyDtoA_v2 = (CUresult (*)(CUarray, size_t, CUdeviceptr, size_t)) __libc_dlsym(libcuda_handle, "cuMemcpyDtoA_v2");
			fprintf(stderr, "cuMemcpyDtoA_v2:%p\n", original_cuMemcpyDtoA_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyDtoA_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyDtoA_v2(dstArray, dstOffset, srcDevice, ByteCount);
		return retval;
	}
}

