#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLinkComplete)(CUlinkState, void **, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLinkComplete(CUlinkState state, void **cubinOut, size_t *sizeOut) {
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
				fprintf(stderr, "dlsym error for fntion cuLinkComplete():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLinkComplete)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLinkComplete = (CUresult (*)(CUlinkState, void **, size_t *)) __libc_dlsym(libcuda_handle, "cuLinkComplete");
			fprintf(stderr, "cuLinkComplete:%p\n", original_cuLinkComplete);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLinkComplete():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLinkComplete(state, cubinOut, sizeOut);
		return retval;
	}
}

