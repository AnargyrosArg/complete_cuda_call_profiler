#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemAllocManaged)(CUdeviceptr *, size_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemAllocManaged(CUdeviceptr *dptr, size_t bytesize, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuMemAllocManaged():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemAllocManaged)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemAllocManaged = (CUresult (*)(CUdeviceptr *, size_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuMemAllocManaged");
			fprintf(stderr, "cuMemAllocManaged:%p\n", original_cuMemAllocManaged);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAllocManaged():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemAllocManaged(dptr, bytesize, flags);
		return retval;
	}
}

