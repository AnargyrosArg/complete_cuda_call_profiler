#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceSetGraphMemAttribute)(CUdevice, CUgraphMem_attribute, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceSetGraphMemAttribute(CUdevice device, CUgraphMem_attribute attr, void *value) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceSetGraphMemAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceSetGraphMemAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceSetGraphMemAttribute = (CUresult (*)(CUdevice, CUgraphMem_attribute, void *)) __libc_dlsym(libcuda_handle, "cuDeviceSetGraphMemAttribute");
			fprintf(stderr, "cuDeviceSetGraphMemAttribute:%p\n", original_cuDeviceSetGraphMemAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceSetGraphMemAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceSetGraphMemAttribute(device, attr, value);
		return retval;
	}
}

