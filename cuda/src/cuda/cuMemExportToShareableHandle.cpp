#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemExportToShareableHandle)(void *, CUmemGenericAllocationHandle, CUmemAllocationHandleType, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemExportToShareableHandle(void *shareableHandle, CUmemGenericAllocationHandle handle, CUmemAllocationHandleType handleType, unsigned long long flags) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemExportToShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemExportToShareableHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemExportToShareableHandle = (CUresult (*)(void *, CUmemGenericAllocationHandle, CUmemAllocationHandleType, unsigned long long)) __libc_dlsym(libcuda_handle, "cuMemExportToShareableHandle");
			fprintf(stderr, "cuMemExportToShareableHandle:%p\n", original_cuMemExportToShareableHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemExportToShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemExportToShareableHandle(shareableHandle, handle, handleType, flags);
		return retval;
	}
}

