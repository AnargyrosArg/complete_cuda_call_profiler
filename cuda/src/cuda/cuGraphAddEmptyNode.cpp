#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddEmptyNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddEmptyNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphAddEmptyNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddEmptyNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddEmptyNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t)) __libc_dlsym(libcuda_handle, "cuGraphAddEmptyNode");
			fprintf(stderr, "cuGraphAddEmptyNode:%p\n", original_cuGraphAddEmptyNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddEmptyNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddEmptyNode(phGraphNode, hGraph, dependencies, numDependencies);
		return retval;
	}
}

