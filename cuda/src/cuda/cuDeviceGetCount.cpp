#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetCount)(int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetCount(int *count) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetCount():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetCount)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetCount = (CUresult (*)(int *)) __libc_dlsym(libcuda_handle, "cuDeviceGetCount");
			fprintf(stderr, "cuDeviceGetCount:%p\n", original_cuDeviceGetCount);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetCount():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetCount(count);
		return retval;
	}
}

