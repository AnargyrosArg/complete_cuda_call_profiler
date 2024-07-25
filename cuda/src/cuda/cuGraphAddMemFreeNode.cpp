#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddMemFreeNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUdeviceptr);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddMemFreeNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, CUdeviceptr dptr) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddMemFreeNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddMemFreeNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddMemFreeNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, CUdeviceptr)) __libc_dlsym(libcuda_handle, "cuGraphAddMemFreeNode");
			fprintf(stderr, "cuGraphAddMemFreeNode:%p\n", original_cuGraphAddMemFreeNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddMemFreeNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddMemFreeNode(phGraphNode, hGraph, dependencies, numDependencies, dptr);
		return retval;
	}
}

