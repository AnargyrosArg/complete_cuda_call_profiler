#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemPrefetchAsync)(CUdeviceptr, size_t, CUdevice, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemPrefetchAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemPrefetchAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemPrefetchAsync = (CUresult (*)(CUdeviceptr, size_t, CUdevice, CUstream)) __libc_dlsym(libcuda_handle, "cuMemPrefetchAsync");
			fprintf(stderr, "cuMemPrefetchAsync:%p\n", original_cuMemPrefetchAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemPrefetchAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemPrefetchAsync(devPtr, count, dstDevice, hStream);
		return retval;
	}
}

