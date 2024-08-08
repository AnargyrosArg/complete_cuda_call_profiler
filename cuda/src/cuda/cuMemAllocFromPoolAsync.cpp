#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemAllocFromPoolAsync)(CUdeviceptr *, size_t, CUmemoryPool, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemAllocFromPoolAsync(CUdeviceptr *dptr, size_t bytesize, CUmemoryPool pool, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemAllocFromPoolAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemAllocFromPoolAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemAllocFromPoolAsync = (CUresult (*)(CUdeviceptr *, size_t, CUmemoryPool, CUstream)) __libc_dlsym(libcuda_handle, "cuMemAllocFromPoolAsync");
			fprintf(stderr, "cuMemAllocFromPoolAsync:%p\n", original_cuMemAllocFromPoolAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAllocFromPoolAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemAllocFromPoolAsync(dptr, bytesize, pool, hStream);
		return retval;
	}
}

