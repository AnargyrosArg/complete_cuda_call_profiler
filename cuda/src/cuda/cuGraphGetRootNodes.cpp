#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphGetRootNodes)(CUgraph, CUgraphNode *, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode *rootNodes, size_t *numRootNodes) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphGetRootNodes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphGetRootNodes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphGetRootNodes = (CUresult (*)(CUgraph, CUgraphNode *, size_t *)) __libc_dlsym(libcuda_handle, "cuGraphGetRootNodes");
			fprintf(stderr, "cuGraphGetRootNodes:%p\n", original_cuGraphGetRootNodes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphGetRootNodes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphGetRootNodes(hGraph, rootNodes, numRootNodes);
		return retval;
	}
}

