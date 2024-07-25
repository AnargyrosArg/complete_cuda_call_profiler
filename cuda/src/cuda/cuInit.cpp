#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuInit)(unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuInit(unsigned int Flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuInit():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuInit)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuInit = (CUresult (*)(unsigned int)) __libc_dlsym(libcuda_handle, "cuInit");
			fprintf(stderr, "original_cuInit:%p\n", original_cuInit);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuInit():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuInit(Flags);
		return retval;
	}
}
