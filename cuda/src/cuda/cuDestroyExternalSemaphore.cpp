#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDestroyExternalSemaphore)(CUexternalSemaphore);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDestroyExternalSemaphore(CUexternalSemaphore extSem) {
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
				fprintf(stderr, "dlsym error for fntion cuDestroyExternalSemaphore():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDestroyExternalSemaphore)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDestroyExternalSemaphore = (CUresult (*)(CUexternalSemaphore)) __libc_dlsym(libcuda_handle, "cuDestroyExternalSemaphore");
			fprintf(stderr, "cuDestroyExternalSemaphore:%p\n", original_cuDestroyExternalSemaphore);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDestroyExternalSemaphore():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDestroyExternalSemaphore(extSem);
		return retval;
	}
}

