#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddKernelNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_KERNEL_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddKernelNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS *nodeParams) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphAddKernelNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddKernelNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddKernelNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_KERNEL_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphAddKernelNode");
			fprintf(stderr, "cuGraphAddKernelNode:%p\n", original_cuGraphAddKernelNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddKernelNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddKernelNode(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
		return retval;
	}
}

