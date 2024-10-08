#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolExportToShareableHandle)(void *, CUmemoryPool, CUmemAllocationHandleType, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolExportToShareableHandle(void *handle_out, CUmemoryPool pool, CUmemAllocationHandleType handleType, unsigned long long flags) {
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
				fprintf(stderr, "dlsym error for fntion cuMemPoolExportToShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolExportToShareableHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolExportToShareableHandle = (CUresult (*)(void *, CUmemoryPool, CUmemAllocationHandleType, unsigned long long)) __libc_dlsym(libcuda_handle, "cuMemPoolExportToShareableHandle");
			fprintf(stderr, "cuMemPoolExportToShareableHandle:%p\n", original_cuMemPoolExportToShareableHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolExportToShareableHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolExportToShareableHandle(handle_out, pool, handleType, flags);
		return retval;
	}
}

