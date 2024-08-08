#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMipmappedArrayGetLevel)(CUarray *, CUmipmappedArray, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMipmappedArrayGetLevel(CUarray *pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level) {
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
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayGetLevel():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMipmappedArrayGetLevel)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMipmappedArrayGetLevel = (CUresult (*)(CUarray *, CUmipmappedArray, unsigned int)) __libc_dlsym(libcuda_handle, "cuMipmappedArrayGetLevel");
			fprintf(stderr, "cuMipmappedArrayGetLevel:%p\n", original_cuMipmappedArrayGetLevel);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayGetLevel():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMipmappedArrayGetLevel(pLevelArray, hMipmappedArray, level);
		return retval;
	}
}

