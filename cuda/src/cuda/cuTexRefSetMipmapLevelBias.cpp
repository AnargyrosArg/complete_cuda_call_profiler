#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetMipmapLevelBias)(CUtexref, float);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetMipmapLevelBias(CUtexref hTexRef, float bias) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmapLevelBias():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetMipmapLevelBias)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetMipmapLevelBias = (CUresult (*)(CUtexref, float)) __libc_dlsym(libcuda_handle, "cuTexRefSetMipmapLevelBias");
			fprintf(stderr, "cuTexRefSetMipmapLevelBias:%p\n", original_cuTexRefSetMipmapLevelBias);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmapLevelBias():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetMipmapLevelBias(hTexRef, bias);
		return retval;
	}
}

