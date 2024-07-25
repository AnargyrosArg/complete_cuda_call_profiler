#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuIpcOpenEventHandle)(CUevent *, CUipcEventHandle);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuIpcOpenEventHandle(CUevent *phEvent, CUipcEventHandle handle) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcOpenEventHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuIpcOpenEventHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuIpcOpenEventHandle = (CUresult (*)(CUevent *, CUipcEventHandle)) __libc_dlsym(libcuda_handle, "cuIpcOpenEventHandle");
			fprintf(stderr, "cuIpcOpenEventHandle:%p\n", original_cuIpcOpenEventHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcOpenEventHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuIpcOpenEventHandle(phEvent, handle);
		return retval;
	}
}

