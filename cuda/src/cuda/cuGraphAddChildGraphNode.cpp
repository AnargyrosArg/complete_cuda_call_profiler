#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddChildGraphNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUgraph);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddChildGraphNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, CUgraph childGraph) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphAddChildGraphNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddChildGraphNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddChildGraphNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUgraph)) __libc_dlsym(libcuda_handle, "cuGraphAddChildGraphNode");
			fprintf(stderr, "cuGraphAddChildGraphNode:%p\n", original_cuGraphAddChildGraphNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddChildGraphNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddChildGraphNode(phGraphNode, hGraph, dependencies, numDependencies, childGraph);
		return retval;
	}
}

