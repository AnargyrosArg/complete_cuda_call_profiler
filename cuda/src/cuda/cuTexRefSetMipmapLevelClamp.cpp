#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetMipmapLevelClamp)(CUtexref, float, float);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetMipmapLevelClamp(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmapLevelClamp():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetMipmapLevelClamp)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetMipmapLevelClamp = (CUresult (*)(CUtexref, float, float)) __libc_dlsym(libcuda_handle, "cuTexRefSetMipmapLevelClamp");
			fprintf(stderr, "cuTexRefSetMipmapLevelClamp:%p\n", original_cuTexRefSetMipmapLevelClamp);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmapLevelClamp():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetMipmapLevelClamp(hTexRef, minMipmapLevelClamp, maxMipmapLevelClamp);
		return retval;
	}
}

