#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPoolExportPointer)(CUmemPoolPtrExportData *, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPoolExportPointer(CUmemPoolPtrExportData *shareData_out, CUdeviceptr ptr) {
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
				fprintf(stderr, "dlsym error for fntion cuMemPoolExportPointer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPoolExportPointer)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPoolExportPointer = (CUresult (*)(CUmemPoolPtrExportData *, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuMemPoolExportPointer");
			fprintf(stderr, "cuMemPoolExportPointer:%p\n", original_cuMemPoolExportPointer);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPoolExportPointer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPoolExportPointer(shareData_out, ptr);
		return retval;
	}
}

