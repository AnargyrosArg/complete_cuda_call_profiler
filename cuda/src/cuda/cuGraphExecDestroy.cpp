#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecDestroy)(CUgraphExec);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecDestroy(CUgraphExec hGraphExec) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphExecDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecDestroy)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecDestroy = (CUresult (*)(CUgraphExec)) __libc_dlsym(libcuda_handle, "cuGraphExecDestroy");
			fprintf(stderr, "cuGraphExecDestroy:%p\n", original_cuGraphExecDestroy);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecDestroy():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecDestroy(hGraphExec);
		return retval;
	}
}

