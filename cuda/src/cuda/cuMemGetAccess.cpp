#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemGetAccess)(unsigned long long *, const CUmemLocation *, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemGetAccess(unsigned long long *flags, const CUmemLocation *location, CUdeviceptr ptr) {
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
				fprintf(stderr, "dlsym error for fntion cuMemGetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemGetAccess)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemGetAccess = (CUresult (*)(unsigned long long *, const CUmemLocation *, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuMemGetAccess");
			fprintf(stderr, "cuMemGetAccess:%p\n", original_cuMemGetAccess);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemGetAccess(flags, location, ptr);
		return retval;
	}
}

