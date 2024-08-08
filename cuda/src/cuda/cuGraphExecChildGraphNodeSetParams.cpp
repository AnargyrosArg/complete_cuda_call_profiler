#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecChildGraphNodeSetParams)(CUgraphExec, CUgraphNode, CUgraph);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecChildGraphNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, CUgraph childGraph) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphExecChildGraphNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecChildGraphNodeSetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecChildGraphNodeSetParams = (CUresult (*)(CUgraphExec, CUgraphNode, CUgraph)) __libc_dlsym(libcuda_handle, "cuGraphExecChildGraphNodeSetParams");
			fprintf(stderr, "cuGraphExecChildGraphNodeSetParams:%p\n", original_cuGraphExecChildGraphNodeSetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecChildGraphNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecChildGraphNodeSetParams(hGraphExec, hNode, childGraph);
		return retval;
	}
}

