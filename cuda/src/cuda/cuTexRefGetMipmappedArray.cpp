#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefGetMipmappedArray)(CUmipmappedArray *, CUtexref);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefGetMipmappedArray(CUmipmappedArray *phMipmappedArray, CUtexref hTexRef) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefGetMipmappedArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefGetMipmappedArray = (CUresult (*)(CUmipmappedArray *, CUtexref)) __libc_dlsym(libcuda_handle, "cuTexRefGetMipmappedArray");
			fprintf(stderr, "cuTexRefGetMipmappedArray:%p\n", original_cuTexRefGetMipmappedArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefGetMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefGetMipmappedArray(phMipmappedArray, hTexRef);
		return retval;
	}
}

