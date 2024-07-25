#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuIpcGetMemHandle)(CUipcMemHandle *, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuIpcGetMemHandle(CUipcMemHandle *pHandle, CUdeviceptr dptr) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcGetMemHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuIpcGetMemHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuIpcGetMemHandle = (CUresult (*)(CUipcMemHandle *, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuIpcGetMemHandle");
			fprintf(stderr, "cuIpcGetMemHandle:%p\n", original_cuIpcGetMemHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcGetMemHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuIpcGetMemHandle(pHandle, dptr);
		return retval;
	}
}

