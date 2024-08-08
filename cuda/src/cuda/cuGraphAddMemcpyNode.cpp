#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddMemcpyNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_MEMCPY3D *, CUcontext);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddMemcpyNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMCPY3D *copyParams, CUcontext ctx) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphAddMemcpyNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddMemcpyNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddMemcpyNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_MEMCPY3D *, CUcontext)) __libc_dlsym(libcuda_handle, "cuGraphAddMemcpyNode");
			fprintf(stderr, "cuGraphAddMemcpyNode:%p\n", original_cuGraphAddMemcpyNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddMemcpyNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddMemcpyNode(phGraphNode, hGraph, dependencies, numDependencies, copyParams, ctx);
		return retval;
	}
}

