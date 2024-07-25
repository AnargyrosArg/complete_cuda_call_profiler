#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamWriteValue32_v2)(CUstream, CUdeviceptr, cuuint32_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamWriteValue32_v2(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamWriteValue32_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamWriteValue32_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamWriteValue32_v2 = (CUresult (*)(CUstream, CUdeviceptr, cuuint32_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamWriteValue32_v2");
			fprintf(stderr, "cuStreamWriteValue32_v2:%p\n", original_cuStreamWriteValue32_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamWriteValue32_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamWriteValue32_v2(stream, addr, value, flags);
		return retval;
	}
}
