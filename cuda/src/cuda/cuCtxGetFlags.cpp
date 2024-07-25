#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxGetFlags)(unsigned int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxGetFlags(unsigned int *flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxGetFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxGetFlags = (CUresult (*)(unsigned int *)) __libc_dlsym(libcuda_handle, "cuCtxGetFlags");
			fprintf(stderr, "cuCtxGetFlags:%p\n", original_cuCtxGetFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxGetFlags(flags);
		return retval;
	}
}

