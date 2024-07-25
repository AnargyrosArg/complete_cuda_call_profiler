#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuWaitExternalSemaphoresAsync)(const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *, unsigned int, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuWaitExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuWaitExternalSemaphoresAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuWaitExternalSemaphoresAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuWaitExternalSemaphoresAsync = (CUresult (*)(const CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *, unsigned int, CUstream)) __libc_dlsym(libcuda_handle, "cuWaitExternalSemaphoresAsync");
			fprintf(stderr, "cuWaitExternalSemaphoresAsync:%p\n", original_cuWaitExternalSemaphoresAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuWaitExternalSemaphoresAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuWaitExternalSemaphoresAsync(extSemArray, paramsArray, numExtSems, stream);
		return retval;
	}
}

