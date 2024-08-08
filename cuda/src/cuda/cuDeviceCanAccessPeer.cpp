#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceCanAccessPeer)(int *, CUdevice, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceCanAccessPeer(int *canAccessPeer, CUdevice dev, CUdevice peerDev) {
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
				fprintf(stderr, "dlsym error for fntion cuDeviceCanAccessPeer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceCanAccessPeer)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceCanAccessPeer = (CUresult (*)(int *, CUdevice, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceCanAccessPeer");
			fprintf(stderr, "cuDeviceCanAccessPeer:%p\n", original_cuDeviceCanAccessPeer);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceCanAccessPeer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceCanAccessPeer(canAccessPeer, dev, peerDev);
		return retval;
	}
}

