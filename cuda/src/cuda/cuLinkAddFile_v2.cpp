#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLinkAddFile_v2)(CUlinkState, CUjitInputType, const char *, unsigned int, CUjit_option *, void **);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLinkAddFile_v2(CUlinkState state, CUjitInputType type, const char *path, unsigned int numOptions, CUjit_option *options, void **optionValues) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkAddFile_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLinkAddFile_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLinkAddFile_v2 = (CUresult (*)(CUlinkState, CUjitInputType, const char *, unsigned int, CUjit_option *, void **)) __libc_dlsym(libcuda_handle, "cuLinkAddFile_v2");
			fprintf(stderr, "cuLinkAddFile_v2:%p\n", original_cuLinkAddFile_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkAddFile_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLinkAddFile_v2(state, type, path, numOptions, options, optionValues);
		return retval;
	}
}

