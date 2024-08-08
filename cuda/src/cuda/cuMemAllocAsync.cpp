#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemAllocAsync)(CUdeviceptr *, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemAllocAsync(CUdeviceptr *dptr, size_t bytesize, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemAllocAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemAllocAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemAllocAsync = (CUresult (*)(CUdeviceptr *, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemAllocAsync");
			fprintf(stderr, "cuMemAllocAsync:%p\n", original_cuMemAllocAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAllocAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemAllocAsync(dptr, bytesize, hStream);
		return retval;
	}
}

