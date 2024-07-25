#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolImportFromShareableHandle)(CUmemoryPool *, void *, CUmemAllocationHandleType, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolImportFromShareableHandle(CUmemoryPool *pool_out, void *handle, CUmemAllocationHandleType handleType, unsigned long long flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolImportFromShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolImportFromShareableHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolImportFromShareableHandle = (CUresult (*)(CUmemoryPool *, void *, CUmemAllocationHandleType, unsigned long long)) __libc_dlsym(libcuda_handle, "cuMemPoolImportFromShareableHandle");
			fprintf(stderr, "cuMemPoolImportFromShareableHandle:%p\n", original_cuMemPoolImportFromShareableHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolImportFromShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolImportFromShareableHandle(pool_out, handle, handleType, flags);
		return retval;
	}
}

