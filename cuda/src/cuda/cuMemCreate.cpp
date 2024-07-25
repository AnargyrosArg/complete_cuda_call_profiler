#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemCreate)(CUmemGenericAllocationHandle *, size_t, const CUmemAllocationProp *, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemCreate(CUmemGenericAllocationHandle *handle, size_t size, const CUmemAllocationProp *prop, unsigned long long flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemCreate = (CUresult (*)(CUmemGenericAllocationHandle *, size_t, const CUmemAllocationProp *, unsigned long long)) __libc_dlsym(libcuda_handle, "cuMemCreate");
			fprintf(stderr, "cuMemCreate:%p\n", original_cuMemCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemCreate(handle, size, prop, flags);
		return retval;
	}
}

