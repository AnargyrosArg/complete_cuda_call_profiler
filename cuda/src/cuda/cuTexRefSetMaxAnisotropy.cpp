#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetMaxAnisotropy)(CUtexref, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetMaxAnisotropy(CUtexref hTexRef, unsigned int maxAniso) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMaxAnisotropy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetMaxAnisotropy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetMaxAnisotropy = (CUresult (*)(CUtexref, unsigned int)) __libc_dlsym(libcuda_handle, "cuTexRefSetMaxAnisotropy");
			fprintf(stderr, "cuTexRefSetMaxAnisotropy:%p\n", original_cuTexRefSetMaxAnisotropy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMaxAnisotropy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetMaxAnisotropy(hTexRef, maxAniso);
		return retval;
	}
}

