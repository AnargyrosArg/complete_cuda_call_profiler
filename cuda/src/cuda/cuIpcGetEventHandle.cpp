#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuIpcGetEventHandle)(CUipcEventHandle *, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuIpcGetEventHandle(CUipcEventHandle *pHandle, CUevent event) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcGetEventHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuIpcGetEventHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuIpcGetEventHandle = (CUresult (*)(CUipcEventHandle *, CUevent)) __libc_dlsym(libcuda_handle, "cuIpcGetEventHandle");
			fprintf(stderr, "cuIpcGetEventHandle:%p\n", original_cuIpcGetEventHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcGetEventHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuIpcGetEventHandle(pHandle, event);
		return retval;
	}
}

