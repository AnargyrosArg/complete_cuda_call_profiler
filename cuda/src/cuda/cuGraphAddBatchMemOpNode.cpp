#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphAddBatchMemOpNode)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_BATCH_MEM_OP_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphAddBatchMemOpNode(CUgraphNode *phGraphNode, CUgraph hGraph, const CUgraphNode *dependencies, size_t numDependencies, const CUDA_BATCH_MEM_OP_NODE_PARAMS *nodeParams) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphAddBatchMemOpNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphAddBatchMemOpNode)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphAddBatchMemOpNode = (CUresult (*)(CUgraphNode *, CUgraph, const CUgraphNode *, size_t, const CUDA_BATCH_MEM_OP_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphAddBatchMemOpNode");
			fprintf(stderr, "cuGraphAddBatchMemOpNode:%p\n", original_cuGraphAddBatchMemOpNode);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphAddBatchMemOpNode():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphAddBatchMemOpNode(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
		return retval;
	}
}

