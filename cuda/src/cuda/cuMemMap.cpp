#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemMap)(CUdeviceptr, size_t, size_t, CUmemGenericAllocationHandle, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemMap(CUdeviceptr ptr, size_t size, size_t offset, CUmemGenericAllocationHandle handle, unsigned long long flags) {
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
				fprintf(stderr, "dlsym error for fntion cuMemMap():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemMap)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemMap = (CUresult (*)(CUdeviceptr, size_t, size_t, CUmemGenericAllocationHandle, unsigned long long)) __libc_dlsym(libcuda_handle, "cuMemMap");
			fprintf(stderr, "cuMemMap:%p\n", original_cuMemMap);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemMap():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemMap(ptr, size, offset, handle, flags);
		return retval;
	}
}

