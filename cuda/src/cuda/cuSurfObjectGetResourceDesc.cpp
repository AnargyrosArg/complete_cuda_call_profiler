#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuSurfObjectGetResourceDesc)(CUDA_RESOURCE_DESC *, CUsurfObject);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUsurfObject surfObject) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfObjectGetResourceDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuSurfObjectGetResourceDesc)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuSurfObjectGetResourceDesc = (CUresult (*)(CUDA_RESOURCE_DESC *, CUsurfObject)) __libc_dlsym(libcuda_handle, "cuSurfObjectGetResourceDesc");
			fprintf(stderr, "cuSurfObjectGetResourceDesc:%p\n", original_cuSurfObjectGetResourceDesc);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfObjectGetResourceDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuSurfObjectGetResourceDesc(pResDesc, surfObject);
		return retval;
	}
}

