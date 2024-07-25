#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleGetSurfRef)(CUsurfref *, CUmodule, const char *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod, const char *name) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleGetSurfRef():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleGetSurfRef)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleGetSurfRef = (CUresult (*)(CUsurfref *, CUmodule, const char *)) __libc_dlsym(libcuda_handle, "cuModuleGetSurfRef");
			fprintf(stderr, "cuModuleGetSurfRef:%p\n", original_cuModuleGetSurfRef);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleGetSurfRef():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleGetSurfRef(pSurfRef, hmod, name);
		return retval;
	}
}

