#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLaunchHostFunc)(CUstream, CUhostFn, void *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void *userData) {
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
				fprintf(stderr, "dlsym error for fntion cuLaunchHostFunc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLaunchHostFunc)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLaunchHostFunc = (CUresult (*)(CUstream, CUhostFn, void *)) __libc_dlsym(libcuda_handle, "cuLaunchHostFunc");
			fprintf(stderr, "cuLaunchHostFunc:%p\n", original_cuLaunchHostFunc);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLaunchHostFunc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLaunchHostFunc(hStream, fn, userData);
		return retval;
	}
}

