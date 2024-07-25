#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetGraphMemAttribute)(CUdevice, CUgraphMem_attribute, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetGraphMemAttribute(CUdevice device, CUgraphMem_attribute attr, void *value) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetGraphMemAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetGraphMemAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetGraphMemAttribute = (CUresult (*)(CUdevice, CUgraphMem_attribute, void *)) __libc_dlsym(libcuda_handle, "cuDeviceGetGraphMemAttribute");
			fprintf(stderr, "cuDeviceGetGraphMemAttribute:%p\n", original_cuDeviceGetGraphMemAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetGraphMemAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetGraphMemAttribute(device, attr, value);
		return retval;
	}
}

