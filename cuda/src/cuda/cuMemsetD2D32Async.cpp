#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemsetD2D32Async)(CUdeviceptr, size_t, unsigned int, size_t, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD2D32Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemsetD2D32Async)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemsetD2D32Async = (CUresult (*)(CUdeviceptr, size_t, unsigned int, size_t, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemsetD2D32Async");
			fprintf(stderr, "cuMemsetD2D32Async:%p\n", original_cuMemsetD2D32Async);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemsetD2D32Async():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemsetD2D32Async(dstDevice, dstPitch, ui, Width, Height, hStream);
		return retval;
	}
}

