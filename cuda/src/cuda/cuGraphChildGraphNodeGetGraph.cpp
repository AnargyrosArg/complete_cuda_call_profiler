#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphChildGraphNodeGetGraph)(CUgraphNode, CUgraph *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph *phGraph) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphChildGraphNodeGetGraph():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphChildGraphNodeGetGraph)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphChildGraphNodeGetGraph = (CUresult (*)(CUgraphNode, CUgraph *)) __libc_dlsym(libcuda_handle, "cuGraphChildGraphNodeGetGraph");
			fprintf(stderr, "cuGraphChildGraphNodeGetGraph:%p\n", original_cuGraphChildGraphNodeGetGraph);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphChildGraphNodeGetGraph():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphChildGraphNodeGetGraph(hNode, phGraph);
		return retval;
	}
}

