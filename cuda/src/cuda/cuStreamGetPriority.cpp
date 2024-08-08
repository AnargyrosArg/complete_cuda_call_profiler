#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuStreamGetPriority)(CUstream, int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuStreamGetPriority(CUstream hStream, int *priority) {
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
				fprintf(stderr, "dlsym error for fntion cuStreamGetPriority():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuStreamGetPriority)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuStreamGetPriority = (CUresult (*)(CUstream, int *)) __libc_dlsym(libcuda_handle, "cuStreamGetPriority");
			fprintf(stderr, "cuStreamGetPriority:%p\n", original_cuStreamGetPriority);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuStreamGetPriority():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuStreamGetPriority(hStream, priority);
		return retval;
	}
}

