#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetMipmapLevelBias)(float *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetMipmapLevelBias(float *pbias, CUtexref hTexRef) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmapLevelBias():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetMipmapLevelBias)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetMipmapLevelBias = (CUresult (*)(float *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetMipmapLevelBias");
			fprintf(stderr, "cuTexRefGetMipmapLevelBias:%p\n", original_cuTexRefGetMipmapLevelBias);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmapLevelBias():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetMipmapLevelBias(pbias, hTexRef);
		return retval;
	}
}

