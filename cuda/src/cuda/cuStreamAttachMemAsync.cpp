#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamAttachMemAsync)(CUstream, CUdeviceptr, size_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamAttachMemAsync(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamAttachMemAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamAttachMemAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamAttachMemAsync = (CUresult (*)(CUstream, CUdeviceptr, size_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamAttachMemAsync");
			fprintf(stderr, "cuStreamAttachMemAsync:%p\n", original_cuStreamAttachMemAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamAttachMemAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamAttachMemAsync(hStream, dptr, length, flags);
		return retval;
	}
}

