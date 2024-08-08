#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemAdvise)(CUdeviceptr, size_t, CUmem_advise, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device) {
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
				fprintf(stderr, "dlsym error for fntion cuMemAdvise():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemAdvise)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemAdvise = (CUresult (*)(CUdeviceptr, size_t, CUmem_advise, CUdevice)) __libc_dlsym(libcuda_handle, "cuMemAdvise");
			fprintf(stderr, "cuMemAdvise:%p\n", original_cuMemAdvise);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAdvise():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemAdvise(devPtr, count, advice, device);
		return retval;
	}
}

