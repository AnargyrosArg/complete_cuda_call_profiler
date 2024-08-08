#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemSetAccess)(CUdeviceptr, size_t, const CUmemAccessDesc *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemSetAccess(CUdeviceptr ptr, size_t size, const CUmemAccessDesc *desc, size_t count) {
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
				fprintf(stderr, "dlsym error for fntion cuMemSetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemSetAccess)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemSetAccess = (CUresult (*)(CUdeviceptr, size_t, const CUmemAccessDesc *, size_t)) __libc_dlsym(libcuda_handle, "cuMemSetAccess");
			fprintf(stderr, "cuMemSetAccess:%p\n", original_cuMemSetAccess);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemSetAccess():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemSetAccess(ptr, size, desc, count);
		return retval;
	}
}

