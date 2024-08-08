#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetExecAffinitySupport)(int *, CUexecAffinityType, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetExecAffinitySupport(int *pi, CUexecAffinityType type, CUdevice dev) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceGetExecAffinitySupport():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetExecAffinitySupport)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetExecAffinitySupport = (CUresult (*)(int *, CUexecAffinityType, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetExecAffinitySupport");
			fprintf(stderr, "cuDeviceGetExecAffinitySupport:%p\n", original_cuDeviceGetExecAffinitySupport);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetExecAffinitySupport():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetExecAffinitySupport(pi, type, dev);
		return retval;
	}
}

