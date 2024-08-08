#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuCtxGetStreamPriorityRange)(int *, int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuCtxGetStreamPriorityRange(int *leastPriority, int *greatestPriority) {
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
				fprintf(stderr, "dlsym error for fntion cuCtxGetStreamPriorityRange():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuCtxGetStreamPriorityRange)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuCtxGetStreamPriorityRange = (CUresult (*)(int *, int *)) __libc_dlsym(libcuda_handle, "cuCtxGetStreamPriorityRange");
			fprintf(stderr, "cuCtxGetStreamPriorityRange:%p\n", original_cuCtxGetStreamPriorityRange);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuCtxGetStreamPriorityRange():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuCtxGetStreamPriorityRange(leastPriority, greatestPriority);
		return retval;
	}
}

