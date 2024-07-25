#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemImportFromShareableHandle)(CUmemGenericAllocationHandle *, void *, CUmemAllocationHandleType);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemImportFromShareableHandle(CUmemGenericAllocationHandle *handle, void *osHandle, CUmemAllocationHandleType shHandleType) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemImportFromShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemImportFromShareableHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemImportFromShareableHandle = (CUresult (*)(CUmemGenericAllocationHandle *, void *, CUmemAllocationHandleType)) __libc_dlsym(libcuda_handle, "cuMemImportFromShareableHandle");
			fprintf(stderr, "cuMemImportFromShareableHandle:%p\n", original_cuMemImportFromShareableHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemImportFromShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemImportFromShareableHandle(handle, osHandle, shHandleType);
		return retval;
	}
}

