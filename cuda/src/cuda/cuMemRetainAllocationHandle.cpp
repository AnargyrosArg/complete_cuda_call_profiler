#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemRetainAllocationHandle)(CUmemGenericAllocationHandle *, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemRetainAllocationHandle(CUmemGenericAllocationHandle *handle, void *addr) {
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
				fprintf(stderr, "dlsym error for fntion cuMemRetainAllocationHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemRetainAllocationHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemRetainAllocationHandle = (CUresult (*)(CUmemGenericAllocationHandle *, void *)) __libc_dlsym(libcuda_handle, "cuMemRetainAllocationHandle");
			fprintf(stderr, "cuMemRetainAllocationHandle:%p\n", original_cuMemRetainAllocationHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemRetainAllocationHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemRetainAllocationHandle(handle, addr);
		return retval;
	}
}

