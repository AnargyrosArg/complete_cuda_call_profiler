#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpy)(CUdeviceptr, CUdeviceptr, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount) {
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
				fprintf(stderr, "dlsym error for fntion cuMemcpy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpy = (CUresult (*)(CUdeviceptr, CUdeviceptr, size_t)) __libc_dlsym(libcuda_handle, "cuMemcpy");
			fprintf(stderr, "cuMemcpy:%p\n", original_cuMemcpy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpy(dst, src, ByteCount);
		return retval;
	}
}

