#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuSurfObjectCreate)(CUsurfObject *, const CUDA_RESOURCE_DESC *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuSurfObjectCreate(CUsurfObject *pSurfObject, const CUDA_RESOURCE_DESC *pResDesc) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfObjectCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuSurfObjectCreate)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuSurfObjectCreate = (CUresult (*)(CUsurfObject *, const CUDA_RESOURCE_DESC *)) __libc_dlsym(libcuda_handle, "cuSurfObjectCreate");
			fprintf(stderr, "cuSurfObjectCreate:%p\n", original_cuSurfObjectCreate);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSurfObjectCreate():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuSurfObjectCreate(pSurfObject, pResDesc);
		return retval;
	}
}

