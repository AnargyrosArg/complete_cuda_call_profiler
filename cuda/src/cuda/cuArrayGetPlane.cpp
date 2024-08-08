#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuArrayGetPlane)(CUarray *, CUarray, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuArrayGetPlane(CUarray *pPlaneArray, CUarray hArray, unsigned int planeIdx) {
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
				fprintf(stderr, "dlsym error for fntion cuArrayGetPlane():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuArrayGetPlane)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuArrayGetPlane = (CUresult (*)(CUarray *, CUarray, unsigned int)) __libc_dlsym(libcuda_handle, "cuArrayGetPlane");
			fprintf(stderr, "cuArrayGetPlane:%p\n", original_cuArrayGetPlane);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayGetPlane():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuArrayGetPlane(pPlaneArray, hArray, planeIdx);
		return retval;
	}
}

