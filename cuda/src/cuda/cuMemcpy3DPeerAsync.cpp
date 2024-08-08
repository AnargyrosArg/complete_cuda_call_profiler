#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemcpy3DPeerAsync)(const CUDA_MEMCPY3D_PEER *, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuMemcpy3DPeerAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemcpy3DPeerAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemcpy3DPeerAsync = (CUresult (*)(const CUDA_MEMCPY3D_PEER *, CUstream)) __libc_dlsym(libcuda_handle, "cuMemcpy3DPeerAsync");
			fprintf(stderr, "cuMemcpy3DPeerAsync:%p\n", original_cuMemcpy3DPeerAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemcpy3DPeerAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemcpy3DPeerAsync(pCopy, hStream);
		return retval;
	}
}

