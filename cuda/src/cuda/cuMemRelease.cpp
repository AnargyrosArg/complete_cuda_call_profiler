#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemRelease)(CUmemGenericAllocationHandle);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemRelease(CUmemGenericAllocationHandle handle) {
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
				fprintf(stderr, "dlsym error for fntion cuMemRelease():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemRelease)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemRelease = (CUresult (*)(CUmemGenericAllocationHandle)) __libc_dlsym(libcuda_handle, "cuMemRelease");
			fprintf(stderr, "cuMemRelease:%p\n", original_cuMemRelease);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemRelease():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemRelease(handle);
		return retval;
	}
}

