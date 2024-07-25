#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphNodeSetEnabled)(CUgraphExec, CUgraphNode, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphNodeSetEnabled(CUgraphExec hGraphExec, CUgraphNode hNode, unsigned int isEnabled) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeSetEnabled():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphNodeSetEnabled)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphNodeSetEnabled = (CUresult (*)(CUgraphExec, CUgraphNode, unsigned int)) __libc_dlsym(libcuda_handle, "cuGraphNodeSetEnabled");
			fprintf(stderr, "cuGraphNodeSetEnabled:%p\n", original_cuGraphNodeSetEnabled);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeSetEnabled():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphNodeSetEnabled(hGraphExec, hNode, isEnabled);
		return retval;
	}
}

