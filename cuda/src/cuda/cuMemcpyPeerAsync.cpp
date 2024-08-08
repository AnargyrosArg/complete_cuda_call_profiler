#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpyPeerAsync)(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemcpyPeerAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpyPeerAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpyPeerAsync = (CUresult (*)(CUdeviceptr, CUcontext, CUdeviceptr, CUcontext, size_t, CUstream)) __libc_dlsym(libcuda_handle, "cuMemcpyPeerAsync");
			fprintf(stderr, "cuMemcpyPeerAsync:%p\n", original_cuMemcpyPeerAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpyPeerAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpyPeerAsync(dstDevice, dstContext, srcDevice, srcContext, ByteCount, hStream);
		return retval;
	}
}

