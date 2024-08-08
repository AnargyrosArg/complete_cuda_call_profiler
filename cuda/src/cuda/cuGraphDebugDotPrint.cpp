#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphDebugDotPrint)(CUgraph, const char *, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphDebugDotPrint(CUgraph hGraph, const char *path, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphDebugDotPrint():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphDebugDotPrint)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphDebugDotPrint = (CUresult (*)(CUgraph, const char *, unsigned int)) __libc_dlsym(libcuda_handle, "cuGraphDebugDotPrint");
			fprintf(stderr, "cuGraphDebugDotPrint:%p\n", original_cuGraphDebugDotPrint);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphDebugDotPrint():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphDebugDotPrint(hGraph, path, flags);
		return retval;
	}
}

