#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetAddressMode)(CUaddress_mode *, CUtexref, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef, int dim) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetAddressMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetAddressMode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetAddressMode = (CUresult (*)(CUaddress_mode *, CUtexref, int)) __libc_dlsym(libcuda_handle, "cuTexRefGetAddressMode");
			fprintf(stderr, "cuTexRefGetAddressMode:%p\n", original_cuTexRefGetAddressMode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetAddressMode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetAddressMode(pam, hTexRef, dim);
		return retval;
	}
}

