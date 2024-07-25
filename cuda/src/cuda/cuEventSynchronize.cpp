#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuEventSynchronize)(CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuEventSynchronize(CUevent hEvent) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventSynchronize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuEventSynchronize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuEventSynchronize = (CUresult (*)(CUevent)) __libc_dlsym(libcuda_handle, "cuEventSynchronize");
			fprintf(stderr, "cuEventSynchronize:%p\n", original_cuEventSynchronize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventSynchronize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuEventSynchronize(hEvent);
		return retval;
	}
}

