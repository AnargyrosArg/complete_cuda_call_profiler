#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLinkCreate_v2)(unsigned int, CUjit_option *, void **, CUlinkState *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLinkCreate_v2(unsigned int numOptions, CUjit_option *options, void **optionValues, CUlinkState *stateOut) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkCreate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLinkCreate_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLinkCreate_v2 = (CUresult (*)(unsigned int, CUjit_option *, void **, CUlinkState *)) __libc_dlsym(libcuda_handle, "cuLinkCreate_v2");
			fprintf(stderr, "cuLinkCreate_v2:%p\n", original_cuLinkCreate_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkCreate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLinkCreate_v2(numOptions, options, optionValues, stateOut);
		return retval;
	}
}

