#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuFlushGPUDirectRDMAWrites)(CUflushGPUDirectRDMAWritesTarget, CUflushGPUDirectRDMAWritesScope);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuFlushGPUDirectRDMAWrites(CUflushGPUDirectRDMAWritesTarget target, CUflushGPUDirectRDMAWritesScope scope) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFlushGPUDirectRDMAWrites():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuFlushGPUDirectRDMAWrites)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuFlushGPUDirectRDMAWrites = (CUresult (*)(CUflushGPUDirectRDMAWritesTarget, CUflushGPUDirectRDMAWritesScope)) __libc_dlsym(libcuda_handle, "cuFlushGPUDirectRDMAWrites");
			fprintf(stderr, "cuFlushGPUDirectRDMAWrites:%p\n", original_cuFlushGPUDirectRDMAWrites);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuFlushGPUDirectRDMAWrites():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuFlushGPUDirectRDMAWrites(target, scope);
		return retval;
	}
}

