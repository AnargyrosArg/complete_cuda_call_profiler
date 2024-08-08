#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetPCIBusId)(char *, int, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetPCIBusId(char *pciBusId, int len, CUdevice dev) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceGetPCIBusId():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetPCIBusId)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetPCIBusId = (CUresult (*)(char *, int, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetPCIBusId");
			fprintf(stderr, "cuDeviceGetPCIBusId:%p\n", original_cuDeviceGetPCIBusId);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetPCIBusId():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetPCIBusId(pciBusId, len, dev);
		return retval;
	}
}

