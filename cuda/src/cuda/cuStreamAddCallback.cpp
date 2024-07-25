#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamAddCallback)(CUstream, CUstreamCallback, void *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamAddCallback(CUstream hStream, CUstreamCallback callback, void *userData, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamAddCallback():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamAddCallback)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamAddCallback = (CUresult (*)(CUstream, CUstreamCallback, void *, unsigned int)) __libc_dlsym(libcuda_handle, "cuStreamAddCallback");
			fprintf(stderr, "cuStreamAddCallback:%p\n", original_cuStreamAddCallback);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamAddCallback():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamAddCallback(hStream, callback, userData, flags);
		return retval;
	}
}

