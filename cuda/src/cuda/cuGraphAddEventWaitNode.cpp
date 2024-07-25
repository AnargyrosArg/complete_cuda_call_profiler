#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddEventWaitNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddEventWaitNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, CUevent event) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddEventWaitNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddEventWaitNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddEventWaitNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent)) __libc_dlsym(libcuda_handle, "cuGraphAddEventWaitNode");
			fprintf(stderr, "cuGraphAddEventWaitNode:%p\n", original_cuGraphAddEventWaitNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddEventWaitNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddEventWaitNode(phGraphNode, hGraph, dependencies, numDependencies, event);
		return retval;
	}
}

