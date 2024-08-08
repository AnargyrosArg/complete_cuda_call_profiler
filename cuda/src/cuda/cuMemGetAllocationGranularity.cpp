#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemGetAllocationGranularity)(size_t *, const CUmemAllocationProp *, CUmemAllocationGranularity_flags);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemGetAllocationGranularity(size_t *granularity, const CUmemAllocationProp *prop, CUmemAllocationGranularity_flags option) {
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
				fprintf(stderr, "dlsym error for fntion cuMemGetAllocationGranularity():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemGetAllocationGranularity)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemGetAllocationGranularity = (CUresult (*)(size_t *, const CUmemAllocationProp *, CUmemAllocationGranularity_flags)) __libc_dlsym(libcuda_handle, "cuMemGetAllocationGranularity");
			fprintf(stderr, "cuMemGetAllocationGranularity:%p\n", original_cuMemGetAllocationGranularity);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetAllocationGranularity():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemGetAllocationGranularity(granularity, prop, option);
		return retval;
	}
}

