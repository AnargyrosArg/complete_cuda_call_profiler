#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphNodeGetEnabled)(CUgraphExec, CUgraphNode, unsigned int *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphNodeGetEnabled(CUgraphExec hGraphExec, CUgraphNode hNode, unsigned int *isEnabled) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetEnabled():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphNodeGetEnabled)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphNodeGetEnabled = (CUresult (*)(CUgraphExec, CUgraphNode, unsigned int *)) __libc_dlsym(libcuda_handle, "cuGraphNodeGetEnabled");
			fprintf(stderr, "cuGraphNodeGetEnabled:%p\n", original_cuGraphNodeGetEnabled);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetEnabled():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphNodeGetEnabled(hGraphExec, hNode, isEnabled);
		return retval;
	}
}

