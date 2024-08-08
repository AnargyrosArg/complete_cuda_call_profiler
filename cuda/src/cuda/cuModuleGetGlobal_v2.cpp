#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuModuleGetGlobal_v2)(CUdeviceptr *, size_t *, CUmodule, const char *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuModuleGetGlobal_v2(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name) {
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
				fprintf(stderr, "dlsym error for fntion cuModuleGetGlobal_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuModuleGetGlobal_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuModuleGetGlobal_v2 = (CUresult (*)(CUdeviceptr *, size_t *, CUmodule, const char *)) __libc_dlsym(libcuda_handle, "cuModuleGetGlobal_v2");
			fprintf(stderr, "cuModuleGetGlobal_v2:%p\n", original_cuModuleGetGlobal_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuModuleGetGlobal_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuModuleGetGlobal_v2(dptr, bytes, hmod, name);
		return retval;
	}
}

