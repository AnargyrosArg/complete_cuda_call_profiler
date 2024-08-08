#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuImportExternalSemaphore)(CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuImportExternalSemaphore(CUexternalSemaphore *extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *semHandleDesc) {
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
				fprintf(stderr, "dlsym error for fntion cuImportExternalSemaphore():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuImportExternalSemaphore)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuImportExternalSemaphore = (CUresult (*)(CUexternalSemaphore *, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *)) __libc_dlsym(libcuda_handle, "cuImportExternalSemaphore");
			fprintf(stderr, "cuImportExternalSemaphore:%p\n", original_cuImportExternalSemaphore);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuImportExternalSemaphore():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuImportExternalSemaphore(extSem_out, semHandleDesc);
		return retval;
	}
}

