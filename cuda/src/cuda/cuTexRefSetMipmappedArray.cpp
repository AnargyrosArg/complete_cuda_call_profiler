#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetMipmappedArray)(CUtexref, CUmipmappedArray, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetMipmappedArray(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetMipmappedArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetMipmappedArray = (CUresult (*)(CUtexref, CUmipmappedArray, unsigned int)) __libc_dlsym(libcuda_handle, "cuTexRefSetMipmappedArray");
			fprintf(stderr, "cuTexRefSetMipmappedArray:%p\n", original_cuTexRefSetMipmappedArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetMipmappedArray(hTexRef, hMipmappedArray, Flags);
		return retval;
	}
}

