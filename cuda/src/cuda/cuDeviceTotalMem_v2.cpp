#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceTotalMem_v2)(size_t *, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceTotalMem_v2(size_t *bytes, CUdevice dev) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceTotalMem_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceTotalMem_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceTotalMem_v2 = (CUresult (*)(size_t *, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceTotalMem_v2");
			fprintf(stderr, "cuDeviceTotalMem_v2:%p\n", original_cuDeviceTotalMem_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceTotalMem_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceTotalMem_v2(bytes, dev);
		return retval;
	}
}

