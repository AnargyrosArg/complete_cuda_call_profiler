#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetByPCIBusId)(CUdevice *, const char *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetByPCIBusId(CUdevice *dev, const char *pciBusId) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceGetByPCIBusId():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetByPCIBusId)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetByPCIBusId = (CUresult (*)(CUdevice *, const char *)) __libc_dlsym(libcuda_handle, "cuDeviceGetByPCIBusId");
			fprintf(stderr, "cuDeviceGetByPCIBusId:%p\n", original_cuDeviceGetByPCIBusId);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetByPCIBusId():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetByPCIBusId(dev, pciBusId);
		return retval;
	}
}

