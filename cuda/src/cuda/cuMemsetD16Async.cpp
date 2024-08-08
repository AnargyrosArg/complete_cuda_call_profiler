#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD16Async)(CUdeviceptr, unsigned short, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemsetD16Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD16Async)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD16Async = (CUresult (*)(CUdeviceptr, unsigned short, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemsetD16Async");
			fprintf(stderr, "cuMemsetD16Async:%p\n", original_cuMemsetD16Async);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD16Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD16Async(dstDevice, us, N, hStream);
		return retval;
	}
}

