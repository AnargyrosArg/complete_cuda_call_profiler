#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemFreeAsync)(CUdeviceptr, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemFreeAsync(CUdeviceptr dptr, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemFreeAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemFreeAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemFreeAsync = (CUresult (*)(CUdeviceptr, CUstream)) __libc_dlsym(libcuda_handle, "cuMemFreeAsync");
			fprintf(stderr, "cuMemFreeAsync:%p\n", original_cuMemFreeAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemFreeAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemFreeAsync(dptr, hStream);
		return retval;
	}
}

