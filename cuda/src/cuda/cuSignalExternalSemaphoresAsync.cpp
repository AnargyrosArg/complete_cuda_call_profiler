#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuSignalExternalSemaphoresAsync)(const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *, unsigned int, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuSignalExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSignalExternalSemaphoresAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuSignalExternalSemaphoresAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuSignalExternalSemaphoresAsync = (CUresult (*)(const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *, unsigned int, CUstream)) __libc_dlsym(libcuda_handle, "cuSignalExternalSemaphoresAsync");
			fprintf(stderr, "cuSignalExternalSemaphoresAsync:%p\n", original_cuSignalExternalSemaphoresAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuSignalExternalSemaphoresAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuSignalExternalSemaphoresAsync(extSemArray, paramsArray, numExtSems, stream);
		return retval;
	}
}

