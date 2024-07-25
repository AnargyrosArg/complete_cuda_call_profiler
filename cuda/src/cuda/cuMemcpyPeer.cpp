#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyPeer)(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyPeer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyPeer)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyPeer = (CUresult (*)(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t)) __libc_dlsym(libcuda_handle, "cuMemcpyPeer");
			fprintf(stderr, "cuMemcpyPeer:%p\n", original_cuMemcpyPeer);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyPeer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyPeer(dstDevice, dstContext, srcDevice, srcContext, ByteCount);
		return retval;
	}
}

