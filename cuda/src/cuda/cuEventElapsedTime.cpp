#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuEventElapsedTime)(float *, CUevent, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuEventElapsedTime(float *pMilliseconds, CUevent hStart, CUevent hEnd) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventElapsedTime():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuEventElapsedTime)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuEventElapsedTime = (CUresult (*)(float *, CUevent, CUevent)) __libc_dlsym(libcuda_handle, "cuEventElapsedTime");
			fprintf(stderr, "cuEventElapsedTime:%p\n", original_cuEventElapsedTime);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuEventElapsedTime():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuEventElapsedTime(pMilliseconds, hStart, hEnd);
		return retval;
	}
}

