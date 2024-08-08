#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexRefSetAddress2D_v3)(CUtexref, const CUDA_ARRAY_DESCRIPTOR *, CUdeviceptr, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexRefSetAddress2D_v3(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch) {
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
				fprintf(stderr, "dlsym error for fntion cuTexRefSetAddress2D_v3():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexRefSetAddress2D_v3)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexRefSetAddress2D_v3 = (CUresult (*)(CUtexref, const CUDA_ARRAY_DESCRIPTOR *, CUdeviceptr, size_t)) __libc_dlsym(libcuda_handle, "cuTexRefSetAddress2D_v3");
			fprintf(stderr, "cuTexRefSetAddress2D_v3:%p\n", original_cuTexRefSetAddress2D_v3);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexRefSetAddress2D_v3():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexRefSetAddress2D_v3(hTexRef, desc, dptr, Pitch);
		return retval;
	}
}

