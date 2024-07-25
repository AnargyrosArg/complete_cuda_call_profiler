#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemHostGetFlags)(unsigned int *, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemHostGetFlags(unsigned int *pFlags, void *p) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemHostGetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemHostGetFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemHostGetFlags = (CUresult (*)(unsigned int *, void *)) __libc_dlsym(libcuda_handle, "cuMemHostGetFlags");
			fprintf(stderr, "cuMemHostGetFlags:%p\n", original_cuMemHostGetFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemHostGetFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemHostGetFlags(pFlags, p);
		return retval;
	}
}

