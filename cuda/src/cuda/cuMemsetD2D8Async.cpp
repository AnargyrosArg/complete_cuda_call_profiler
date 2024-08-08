#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD2D8Async)(CUdeviceptr, size_t, unsigned char, size_t, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemsetD2D8Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD2D8Async)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD2D8Async = (CUresult (*)(CUdeviceptr, size_t, unsigned char, size_t, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemsetD2D8Async");
			fprintf(stderr, "cuMemsetD2D8Async:%p\n", original_cuMemsetD2D8Async);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD2D8Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD2D8Async(dstDevice, dstPitch, uc, Width, Height, hStream);
		return retval;
	}
}

