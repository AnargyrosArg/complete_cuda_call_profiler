#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphGetNodes)(CUgraph, CUgraphNode *, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphGetNodes(CUgraph hGraph, CUgraphNode *nodes, size_t *numNodes) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphGetNodes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphGetNodes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphGetNodes = (CUresult (*)(CUgraph, CUgraphNode *, size_t *)) __libc_dlsym(libcuda_handle, "cuGraphGetNodes");
			fprintf(stderr, "cuGraphGetNodes:%p\n", original_cuGraphGetNodes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphGetNodes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphGetNodes(hGraph, nodes, numNodes);
		return retval;
	}
}

