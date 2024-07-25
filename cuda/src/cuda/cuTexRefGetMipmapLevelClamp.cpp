#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetMipmapLevelClamp)(float *, float *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, CUtexref hTexRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmapLevelClamp():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetMipmapLevelClamp)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetMipmapLevelClamp = (CUresult (*)(float *, float *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetMipmapLevelClamp");
			fprintf(stderr, "cuTexRefGetMipmapLevelClamp:%p\n", original_cuTexRefGetMipmapLevelClamp);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmapLevelClamp():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetMipmapLevelClamp(pminMipmapLevelClamp, pmaxMipmapLevelClamp, hTexRef);
		return retval;
	}
}

