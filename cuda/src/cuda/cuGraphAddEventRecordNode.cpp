#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddEventRecordNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddEventRecordNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, CUevent event) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphAddEventRecordNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddEventRecordNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddEventRecordNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUevent)) __libc_dlsym(libcuda_handle, "cuGraphAddEventRecordNode");
			fprintf(stderr, "cuGraphAddEventRecordNode:%p\n", original_cuGraphAddEventRecordNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddEventRecordNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddEventRecordNode(phGraphNode, hGraph, dependencies, numDependencies, event);
		return retval;
	}
}

