#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuIpcOpenMemHandle_v2)(CUdeviceptr *, CUipcMemHandle, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuIpcOpenMemHandle_v2(CUdeviceptr *pdptr, CUipcMemHandle handle, unsigned int Flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcOpenMemHandle_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuIpcOpenMemHandle_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuIpcOpenMemHandle_v2 = (CUresult (*)(CUdeviceptr *, CUipcMemHandle, unsigned int)) __libc_dlsym(libcuda_handle, "cuIpcOpenMemHandle_v2");
			fprintf(stderr, "cuIpcOpenMemHandle_v2:%p\n", original_cuIpcOpenMemHandle_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuIpcOpenMemHandle_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuIpcOpenMemHandle_v2(pdptr, handle, Flags);
		return retval;
	}
}

