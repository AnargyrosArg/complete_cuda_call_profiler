#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemGetAllocationPropertiesFromHandle)(CUmemAllocationProp *, CUmemGenericAllocationHandle);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemGetAllocationPropertiesFromHandle(CUmemAllocationProp *prop, CUmemGenericAllocationHandle handle) {
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
				fprintf(stderr, "dlsym error for fntion cuMemGetAllocationPropertiesFromHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemGetAllocationPropertiesFromHandle)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemGetAllocationPropertiesFromHandle = (CUresult (*)(CUmemAllocationProp *, CUmemGenericAllocationHandle)) __libc_dlsym(libcuda_handle, "cuMemGetAllocationPropertiesFromHandle");
			fprintf(stderr, "cuMemGetAllocationPropertiesFromHandle:%p\n", original_cuMemGetAllocationPropertiesFromHandle);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemGetAllocationPropertiesFromHandle():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemGetAllocationPropertiesFromHandle(prop, handle);
		return retval;
	}
}

