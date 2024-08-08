#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemHostGetDevicePointer_v2)(CUdeviceptr *, void *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemHostGetDevicePointer_v2(CUdeviceptr *pdptr, void *p, unsigned int Flags) {
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
				fprintf(stderr, "dlsym error for fntion cuMemHostGetDevicePointer_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemHostGetDevicePointer_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemHostGetDevicePointer_v2 = (CUresult (*)(CUdeviceptr *, void *, unsigned int)) __libc_dlsym(libcuda_handle, "cuMemHostGetDevicePointer_v2");
			fprintf(stderr, "cuMemHostGetDevicePointer_v2:%p\n", original_cuMemHostGetDevicePointer_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemHostGetDevicePointer_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemHostGetDevicePointer_v2(pdptr, p, Flags);
		return retval;
	}
}

