#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolImportPointer)(CUdeviceptr *, CUmemoryPool, CUmemPoolPtrExportData *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolImportPointer(CUdeviceptr *ptr_out, CUmemoryPool pool, CUmemPoolPtrExportData *shareData) {
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
				fprintf(stderr, "dlsym error for fntion cuMemPoolImportPointer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolImportPointer)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolImportPointer = (CUresult (*)(CUdeviceptr *, CUmemoryPool, CUmemPoolPtrExportData *)) __libc_dlsym(libcuda_handle, "cuMemPoolImportPointer");
			fprintf(stderr, "cuMemPoolImportPointer:%p\n", original_cuMemPoolImportPointer);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolImportPointer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolImportPointer(ptr_out, pool, shareData);
		return retval;
	}
}

